# include "payment.h"

# include <cstdio>
# include <cstdlib>
# include <cstring>

# define KEY_SIZE 128

/* Simula o gateway de pagamentos, que aceita o pagamento quando a chave foi informada e o valor é positivo. */
static bool gatewayAuthorize(const char *key, double amount)
{
    return key[0] != '\0' && amount > 0.0;
}

/* Autoriza o pagamento com a chave do gateway e apaga a chave da memória logo depois do uso.
   A chave agora vem da variavel de ambiente PAYMENT_KEY e nao fica mais escrita no codigo. */
bool processPayment(double amount)
{
    char key[KEY_SIZE];
    char *chave;
    bool authorized;

    chave = getenv("PAYMENT_KEY");

    /* se a variavel nao existir, nao tem chave e o pagamento e recusado */
    if (chave == NULL)
    {
        return false;
    }

    snprintf(key, sizeof key, "%s", chave);
    authorized = gatewayAuthorize(key, amount);
    /* explicit_bzero no lugar do memset, pq o compilador pode tirar o memset na otimizacao */
    explicit_bzero(key, sizeof key);
    return authorized;
}
