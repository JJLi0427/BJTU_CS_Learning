#include <iostream>
#include <cstring>
#include <vector>
#include <curl/curl.h>

size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    std::string *uploadData = static_cast<std::string*>(userp);
    size_t uploadSize = uploadData->size();

    if(size*nmemb < 1)
        return 0;

    if(uploadSize) {
        size_t copySize = size*nmemb;
        if(copySize > uploadSize)
            copySize = uploadSize;

        memcpy(ptr, uploadData->c_str(), copySize);
        uploadData->erase(0, copySize);

        return copySize;
    }

    return 0;
}

void sendEmail(
    const std::string& smtpServer, 
    const std::string& from, 
    const std::vector<std::string>& to, 
    const std::string& password, 
    const std::string& subject, 
    const std::string& body
) {
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, from.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, smtpServer.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from.c_str());
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        for(const auto& recipient : to) {
            recipients = curl_slist_append(recipients, recipient.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        std::string email = "To: " + to[0] + "\r\n" +
                            "From: " + from + "\r\n" +
                            "Subject: " + subject + "\r\n\r\n" +
                            body;

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &email);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}

int main() {
    std::string smtpServer = "smtp://mail.bjtu.edu.cn:25";

    std::string from;
    std::cout << "Enter your email address: ";
    std::getline(std::cin, from);

    std::string password;
    std::cout << "Enter your email password: ";
    std::getline(std::cin, password);

    std::cout << "Enter recipient email addresses nums: ";
    int n;
    std::cin >> n;
    std::vector<std::string> to;
    std::string email;
    for (int i = 0; i < n; i++) {
        std::cout << "Enter recipient email address " << i+1 << ": ";
        std::cin >> email;
        to.push_back(email);
    }

    std::string subject;
    std::cout << "Enter email subject: ";
    std::getline(std::cin >> std::ws, subject);

    std::string body;
    std::cout << "Enter email message: ";
    std::getline(std::cin, body);

    sendEmail(smtpServer, from, to, password, subject, body);

    return 0;
}