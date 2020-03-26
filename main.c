#include <stdio.h>
#include "vector.h"
#include "test.h"

int main() {
    int shut_down = 0;
    while (!shut_down) {
        printf("Введите 0, если хотите завершить работу программы.\nВведите 1, если хотите вычислить сумму двух векторов.\nВведите 2, если хотите cкалярно умножить два вектора. \nВведите 3, если хотите запустить тесты.\n-> ");
        int user_input;
        scanf("%d", &user_input);
        if (user_input == 0){
            shut_down = 1;
        }
        else if (user_input == 1) {
            printf("\nВведите разметрность векторов, с которыми будет выполняться операция сложения.\n-> ");
            int n;
            scanf("%d", &n);
            printf("\nВведите 1, если вектора будут состоять из вещественных чисел, в противнои случае, если вектора будут состоять из комплексных чисел, введите 2.\n-> ");
            int v_type;
            scanf("%d", &v_type);
            int el_size;
            if (v_type == 1){
                el_size = sizeof(float);
            }
            else {
                el_size = sizeof(complex);
            }
            printf("\nЗаполните вектора a и b, сдедуя следующим правилам:\n\t1. Каждый элемент вектора отделятся пробелом от предыдущего.\n\t2. Вектор может содержать либо комплексные, либо вещественные числа (формат комплексных: a+i*b / a-i*b / -a+i*b / -a-i*b  (без пробелов между символами, где a и b - вещественные числа с форматом i.f, где i - целая часть, а f - дробная, формат вещественных: i.f / -i.f\n\na:\n\n");
            getchar();
            vector *vec1 = set_vector(n, el_size);
            printf("\nb:\n\n");
            vector *vec2 = set_vector(n, el_size);
            vector *vec3;
            if (v_type == 1){
                vec3 = sum_vector(vec1, vec2, sum_float);
            }
            else {
                vec3 = sum_vector(vec1, vec2, sum_complex);
            }
            printf("\nВектор, полученный в результате сложения вектора a и вектора b:\n\n");
            print_vector(vec3);
            printf("\n");
        }
        else if (user_input == 2) {
            printf("\nВведите разметрность вектора, с которым будет выполняться операция умножения на скаляр.\n-> ");
            int n;
            scanf("%d", &n);
            printf("\nВведите 1, если вектор будет состоять из вещественных чисел, в противнои случае, если вектор будет состоять из комплексных чисел, введите 2.\n-> ");
            int v_type;
            scanf("%d", &v_type);
            int el_size;
            if (v_type == 1){
                el_size = sizeof(float);
            }
            else {
                el_size = sizeof(complex);
            }
            printf("\nЗаполните вектора a и b, сдедуя следующим правилам:\n\t1. Каждый элемент вектора отделятся пробелом от предыдущего.\n\t2. Вектор может содержать либо комплексные, либо вещественные числа (формат комплексных: a+i*b / a-i*b / -a+i*b / -a-i*b  (без пробелов между символами, где a и b - вещественные числа с форматом i.f, где i - целая часть, а f - дробная, формат вещественных: i.f / -i.f\n\na:\n\n");
            getchar();
            vector *vec1 = set_vector(n, el_size);
            printf("\nb:\n\n");
            vector *vec2 = set_vector(n, el_size);
            if (v_type == 1){
                void *buff_scal_multip = scalar_multip_vector(vec1, vec2, multip_float, sum_float);
                printf("\nСкаляр, полученный в результате умнажения вектора a на вектор b: %.2f\n", *(float *)buff_scal_multip);
            }
            else {
                void *buff_scal_multip = scalar_multip_vector(vec1, vec2, multip_complex, sum_complex);
                printf("\nСкаляр, полученный в результате умнажения вектора a на вектор b: %.2f+i*(%.2f)\n", ((complex *)buff_scal_multip)->re, ((complex *)buff_scal_multip)->im);
            }
            printf("\n");
        }
        else if (user_input == 3){
            start_test();
        }
        else {
            printf("Некореектный ввод, повторите попытку!\n");
        }
    }
    return 0;
}
