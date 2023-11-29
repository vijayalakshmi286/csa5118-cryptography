#include <stdio.h>
#include <math.h>

int main() 
{
    double total_keys = tgamma(26 + 1);  
    double unique_keys = total_keys / tgamma(2 + 1); 
    int total_keys_power_of_2 = log2(total_keys);
    int unique_keys_power_of_2 = log2(unique_keys);
    printf("Total keys: %.0f (approximately 2^%d)\n", total_keys, total_keys_power_of_2);
    printf("Unique keys (considering 'I' and 'J' as interchangeable): %.0f (approximately 2^%d)\n", unique_keys, unique_keys_power_of_2);

    return 0;
}
