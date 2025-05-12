#include <stdio.h>
 
int main() {
    float renda, imposto;
    
    scanf("%f", &renda);
    
    if(renda > 4500.00) {
        
        imposto = (1000.00 * 0.08) + (1500.00 * 0.18) + ((renda - 4500.00) * 0.28);
        printf("R$ %.2f\n", imposto);
        
    } else if(3000.01 <= renda && renda <= 4500.00) {
        
        imposto = ((1000.00 * 0.08) + ((renda - 3000.00) * 0.18));
        printf("R$ %.2f\n", imposto);
        
    } else if(2000.01 <= renda && renda <= 3000.00) {  
        
        imposto = ((renda - 2000.00) * 0.08);
        printf("R$ %.2f\n", imposto);
        
    } else if(0 <= renda && renda <= 2000.00) {
        printf("Isento\n");
        
    }        
 
    return 0;
}
