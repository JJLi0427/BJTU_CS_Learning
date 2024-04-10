#include <iostream>
#include <curl/curl.h>

size_t write_callback(char *buffer, size_t size, size_t nitems, void *userp) {
    std::string *response = static_cast<std::string*>(userp);
    size_t totalSize = size * nitems;
    response->append(buffer, totalSize);
    return totalSize;
}

void receiveEmail(const std::string& pop3Server, const std::string& username, const std::string& password) {
    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, pop3Server.c_str());
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        else
            std::cout << response << std::endl;

        curl_easy_cleanup(curl);
    }
}

int main() {
    std::string pop3Server = "pop3://pop-mail.outlook.com";

    std::string username;
    std::cout << "Enter your email address: ";
    std::getline(std::cin, username);

    std::string password;
    std::cout << "Enter your email password: ";
    std::getline(std::cin, password);

    receiveEmail(pop3Server, username, password);

    return 0;
}