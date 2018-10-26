#include <iostream>
#include <thread>
#include <atomic>
#include <bitset>
#define NUM_THREADS 2
#define NUM_KEY 4

using namespace std;

char caracter;
atomic<int> res;

//Struct para poder mandar el char y la contrasena en cada ronda
struct thread_data {
   int  key;
   char  caracter;
};

//Aplicacion del XOR
void *Encrypt(void* arg_srtuct){
    struct thread_data *datos_func = (struct thread_data *)arg_srtuct;
    datos_func = (struct thread_data *) arg_srtuct;
    int* valor = new int;
    *valor = *((int*)(void*)&datos_func->caracter);
    res = (*valor) ^ datos_func->key;
    return NULL;   
}

/*
//pendiente pero posible
int *Separar(void* argv){
    int* valor = new int;
    int* decrypt = new int;
    *valor = *((int*)argv);
    *decrypt = (*valor) ^ key;
    return (int*)decrypt;
}*/

int main() {
    pthread_t threads[NUM_THREADS];
    
    int char_R;
    int char_L;
    //llaves
    int keys[NUM_KEY] {0b1001,0b1101,0b0011,0b0101};

    //argumentos a mandar en cada ronda de encripcion
    struct thread_data arg_ronda;
    
    //caracter a encriptar
    caracter = 'a';
    cout << "El caracter es:  " << caracter <<  endl;

    //imprimir la llave
    bitset<8> key_b(keys[0]);
    cout << "La llave es: " << key_b <<  endl;
    
    //transformacion en binario
    bitset<8> x(caracter);
    cout << "El binario del caracter es: " << x << endl;

    //dividir en dos el binario
    char_R = caracter >> 4;
    bitset<8> x2 (char_R);
    cout << "La primera mitad del binario: " << (x2<<4) << endl;
    char_L = (caracter && 00001111);
    bitset<8> x3 (char_L);
    cout << "La segunda mitad del binario: " << (x3) << endl;

    //Primera ronda 
    arg_ronda.caracter = char_R;
    arg_ronda.key = keys[0];
    pthread_create(&threads[0], NULL, Encrypt, (void*) &arg_ronda);
	pthread_join(threads[0], NULL); 
    bitset<8> res1(res);
    cout<< "Esta es la respuesta en la ronda 1: " << res <<" Este es el binario: "<< (res1<<4) <<endl;
    
    //Segunda ronda 
    arg_ronda.caracter = char_L;
    arg_ronda.key = keys[0];
    pthread_create(&threads[1], NULL, Encrypt, (void*) &arg_ronda);
	pthread_join(threads[1], NULL); 
    bitset<8> res2(res);
    cout<< "Esta es la respuesta en la ronda 2: " << res <<" Este es el binario: "<< res2 <<endl;

    //Resultado
    bitset<8> outp;
    outp = (res1<<4) | res2;
    cout << "La respuesta final seria: " << outp << endl;

    //Desencriptar
    
  return 0;
}
