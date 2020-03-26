#ifndef D_PROJECT_TEST_H
#define D_PROJECT_TEST_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "vector.h"

    struct Errors {
        int *error_code;
        char **error_description;
        int *error;
        int count;
    };

    typedef struct Errors errors;

    void create_errors(errors **);
    void start_test();

    void test_create_complex_num(errors **, int);
    void test_multip_complex(errors **, int);
    void test_sum_vector(errors **, int);
    void test_scalar_multip_vector(errors **err, int cnt_t);

    void copy_string(char [], char **);

    void copy_string(char s1[], char **s2){
        int n = len_c(s1);
        char *buff = (char *)malloc(n * sizeof(char));
        for (int i = 0; i < n; ++i){
            buff[i] = s1[i];
        }
        *s2 = buff;
    }

    void start_test(){
        errors *err;
        create_errors(&err);
        errors *s_err = err;
        test_create_complex_num(&err, 6);
        test_multip_complex(&err, 6);
        test_sum_vector(&err, 10);
        test_scalar_multip_vector(&err, 10);
        int n = s_err->count;
        for (int i = 0; i < n; ++i){
            if ((s_err->error)[i] == 1){
                printf("TEST: [%d]\t|\tERROR CODE: [%d]\t|\tSTATUS: [ERR]\t|\tDESCRIPTION: [%s]\n", i + 1, (s_err->error_code)[i], (s_err->error_description)[i]);
            }
            else {
                printf("TEST: [%d]\t|\tSTATUS: [OK]\n", i + 1, (s_err->error_code)[i]);
            }
        }
    }

    void create_errors(errors **errs){
        errors *n_errs = (errors *)malloc(sizeof(errors));
        int *err_c = (int *)malloc(0 * sizeof(int));
        char **err_desc = (char **)malloc(0 * sizeof(char *));
        int *err = (int *)malloc(0 * sizeof(int));
        n_errs->count = 0;
        n_errs->error_code = err_c;
        n_errs->error_description = err_desc;
        n_errs->error = err;
        *errs = n_errs;
    }

    void test_create_complex_num(errors **err, int cnt_t){
        complex *compl;
        int flag = 0;
        for (int i = 0; i < cnt_t; ++i){
            create_complex_num(&compl, (float)i + 2.2f, (float)i * 4.1f + 5.0f);
            if ((compl->re != (float)i + 2.2f) || (compl->im != (float)i * 4.1f + 5.0f)){
                flag = 1;
                break;
            }
        }
        errors *s_err = *err;
        int n = s_err->count;
        s_err->error_code = (int *)realloc(s_err->error_code, (n + 1) * sizeof(int));
        s_err->error_description = (char **)realloc(s_err->error_description, (n + 1) * sizeof(char *));
        s_err->error = (int *)realloc(s_err->error, (n + 1) * sizeof(int));
        ++(s_err->count);
        (s_err->error_code)[n] = 201;
        char buff_s[] = "Incorrect function operation <create_complex_num>";
        char *buff;
        copy_string(buff_s, &buff);
        (s_err->error_description)[n] = buff;
        (s_err->error)[n] = flag;
    }

    void test_multip_complex(errors **err, int cnt_t){
        complex *compl1;
        complex *compl2;
        complex *compl3;
        int flag = 0;
        for (int i = 0; i < cnt_t; ++i){
            create_complex_num(&compl1, (float)i + 2.2f, (float)i * 4.1f + 5.0f);
            create_complex_num(&compl2, (float)i - 2.2f, (float)i * 6.1f - 5.0f);
            compl3 = multip_complex(compl1, compl2);
            if (((((float)i + 2.2f) * ((float)i - 2.2f) - ((float)i * 4.1f + 5.0f) * ((float)i * 6.1f - 5.0f)) != compl3->re) || ((((float)i + 2.2f) * ((float)i * 6.1f - 5.0f) + ((float)i * 4.1f + 5.0f) * ((float)i - 2.2f)) != compl3->im)){
                flag = 1;
                break;
            }
        }
        errors *s_err = *err;
        int n = s_err->count;
        s_err->error_code = (int *)realloc(s_err->error_code, (n + 1) * sizeof(int));
        s_err->error_description = (char **)realloc(s_err->error_description, (n + 1) * sizeof(char *));
        s_err->error = (int *)realloc(s_err->error, (n + 1) * sizeof(int));
        ++(s_err->count);
        (s_err->error_code)[n] = 204;
        char buff_s[] = "Incorrect function operation <multip_complex>";
        char *buff;
        copy_string(buff_s, &buff);
        (s_err->error_description)[n] = buff;
        (s_err->error)[n] = flag;
    }

    void test_sum_vector(errors **err, int cnt_t){
        int flag = 0;
        for (int i = 1; i < cnt_t + 10; ++i){
            vector *vec1;
            vec1 = create_vector(i, sizeof(float));
            vector *vec2;
            vec2 = create_vector(i, sizeof(float));
            for (int j = 0; j < i; ++j){
                float *buff_f1 = (float *)malloc(sizeof(float));
                float *buff_f2 = (float *)malloc(sizeof(float));
                *buff_f1 = (float)i + (float)j;
                *buff_f2 = (float)i * (float)j;
                set_element(vec1, buff_f1, j);
                set_element(vec2, buff_f2, j);
            }
            vector *vec3 = sum_vector(vec1, vec2, sum_float);
            for (int j = 0; j < i; ++j){
                if (*(float *)get_element(vec3, j) != ((float)i + (float)j + (float)i * (float)j)){
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        errors *s_err = *err;
        int n = s_err->count;
        s_err->error_code = (int *)realloc(s_err->error_code, (n + 1) * sizeof(int));
        s_err->error_description = (char **)realloc(s_err->error_description, (n + 1) * sizeof(char *));
        s_err->error = (int *)realloc(s_err->error, (n + 1) * sizeof(int));
        ++(s_err->count);
        (s_err->error_code)[n] = 202;
        char buff_s[] = "Incorrect function operation <sum_vector>";
        char *buff;
        copy_string(buff_s, &buff);
        (s_err->error_description)[n] = buff;
        (s_err->error)[n] = flag;
    }

    void test_scalar_multip_vector(errors **err, int cnt_t){
        int flag = 0;
        for (int i = 1; i < cnt_t + 10; ++i){
            vector *vec1;
            vec1 = create_vector(i, sizeof(float));
            vector *vec2;
            vec2 = create_vector(i, sizeof(float));
            float t_buff_scalar = 0;
            for (int j = 0; j < i; ++j){
                float *buff_f1 = (float *)malloc(sizeof(float));
                float *buff_f2 = (float *)malloc(sizeof(float));
                *buff_f1 = (float)i + (float)j;
                *buff_f2 = (float)i * (float)j;
                set_element(vec1, buff_f1, j);
                set_element(vec2, buff_f2, j);
                t_buff_scalar += *buff_f1 * *buff_f2;
            }
            void *buff_scalar = scalar_multip_vector(vec1, vec2, multip_float, sum_float);
            if (*(float *)buff_scalar != t_buff_scalar){
                flag = 1;
                break;
            }
        }
        errors *s_err = *err;
        int n = s_err->count;
        s_err->error_code = (int *)realloc(s_err->error_code, (n + 1) * sizeof(int));
        s_err->error_description = (char **)realloc(s_err->error_description, (n + 1) * sizeof(char *));
        s_err->error = (int *)realloc(s_err->error, (n + 1) * sizeof(int));
        ++(s_err->count);
        (s_err->error_code)[n] = 205;
        char buff_s[] = "Incorrect function operation <scalar_multip_vector>";
        char *buff;
        copy_string(buff_s, &buff);
        (s_err->error_description)[n] = buff;
        (s_err->error)[n] = flag;
    }


#endif
