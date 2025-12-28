#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#include "../include/network.h"

/* callback для записи данных curl */
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    FILE *file = (FILE *)userp;

    if (!file) {
        return 0;
    }

    return fwrite(contents, size, nmemb, file);
}

/* Инициализация сети */
int init_network(void) {
    CURLcode res = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (res != CURLE_OK) {
        fprintf(stderr, "libcurl init error: %s\n", curl_easy_strerror(res));
        return -1;
    }

    printf("[NETWORK] libcurl initialized\n");
    return 0;
}

/* Очистка сети */
void cleanup_network(void) {
    curl_global_cleanup();
    printf("[NETWORK] libcurl cleaned up\n");
}

/* Загрузка файла по URL */
int download_file(const char *url, const char *output_filename) {
    if (!url || !output_filename) {
        fprintf(stderr, "download_file: invalid arguments\n");
        return -1;
    }

    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to create CURL handle\n");
        return -1;
    }

    FILE *file = fopen(output_filename, "wb");
    if (!file) {
        perror("fopen");
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "student_system/1.0");
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

    CURLcode res = curl_easy_perform(curl);
    fclose(file);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_easy_cleanup(curl);
    printf("[NETWORK] File downloaded: %s\n", output_filename);

    return 0;
}
