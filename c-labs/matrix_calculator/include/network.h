#ifndef NETWORK_H
#define NETWORK_H

int init_network(void);
void cleanup_network(void);
int download_file(const char* url, const char* output_filename);

#endif
