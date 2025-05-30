#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <filesystem>

namespace fs = std::filesystem;

// Callback-функция для записи полученных данных в строку
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Функция для загрузки страницы по URL
bool downloadPage(const std::string& url, std::string& output) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Ошибка инициализации CURL" << std::endl;
        return false;
    }

    CURLcode res;
    std::string readBuffer;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0"); //  User-Agent

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "Ошибка CURL: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    output = readBuffer;
    return true;
}

// Функция для генерации имени файла на основе URL
std::string generateFilename(const std::string& url) {
    std::string filename = url;
    
    for (char& c : filename) {
        if (c == '/' || c == ':' || c == '?' || c == '&' || c == '=') {
            c = '_';
        }
    }
    
    if (filename.length() > 100) {
        filename = filename.substr(0, 100);
    }
    
    return filename + ".html";
}

// Функция для чтения URL
std::vector<std::string> readUrlsFromFile(const std::string& filename) {
    std::vector<std::string> urls;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return urls;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            urls.push_back(line);
        }
    }
    
    file.close();
    return urls;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: " << argv[0] << " <файл_с_url.txt>" << std::endl;
        return 1;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    // Читаем URL
    std::vector<std::string> urls = readUrlsFromFile(argv[1]);
    
    if (urls.empty()) {
        std::cerr << "Не найдено URL для обработки" << std::endl;
        curl_global_cleanup();
        return 1;
    }
    
    // Создаем папку для сохранения страниц
    if (!fs::exists("downloaded_pages")) {
        fs::create_directory("downloaded_pages");
    }
    
    // Обрабатываем каждый URL
    for (const auto& url : urls) {
        std::cout << "Обработка URL: " << url << std::endl;
        
        std::string pageContent;
        if (downloadPage(url, pageContent)) {
            std::string filename = "downloaded_pages/" + generateFilename(url);
            
            std::ofstream outFile(filename);
            if (outFile.is_open()) {
                outFile << pageContent;
                outFile.close();
                std::cout << "Страница сохранена в: " << filename << std::endl;
            } else {
                std::cerr << "Не удалось создать файл: " << filename << std::endl;
            }
        } else {
            std::cerr << "Не удалось загрузить страницу: " << url << std::endl;
        }
    }
    curl_global_cleanup();
    
    return 0;
}
