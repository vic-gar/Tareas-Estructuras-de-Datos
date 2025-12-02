/*
 * funciones.h
 *
 *  Created on: 25/08/2025
 *      Author: Víctor A. García 
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>

class Funciones {
    public:
        int sumaIterativa(int n){
            int sum = 0;
            for (int i = 1; i <= n; i++){
                sum = sum + i;
            }
            return sum;
        }

        int sumaRecursiva(int n){
            if (n < 1){
                return 0;
            } else{
                return sumaRecursiva(n - 1) + n;
            }
        }

        int sumaDirecta(int n){
            return (n * (n + 1)) / 2;
        }
};

#endif