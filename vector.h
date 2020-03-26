
#ifndef D_PROJECT_VECTOR_H
#define D_PROJECT_VECTOR_H

    #include "stdlib.h"
    #include "string.h"

    struct Compl {
        float im;
        float re;
    };

    struct Vector {
        void *data;
        int element_size;
        int size;
    };

    typedef struct Compl complex;
    typedef struct Vector vector;

    vector *create_vector(int, int);
    void set_element(vector *, void *, int);
    vector *set_vector(int, int);
    vector *sum_vector(vector *, vector*, void *(*)(void *, void *));
    void *scalar_multip_vector(vector *vec1, vector *vec2, void *(*multip)(void *, void *), void *(*sum)(void *, void *));
    void *get_element(vector *, int);

    void create_complex_num(complex **, float , float);
    void *multip_complex(void *, void *);
    void convert_to_complex_num(complex **, char []);
    void *sum_complex(void *, void *);

    int len_c(char []);
    int to_int(char []);
    int len_i(int);
    int power(int, int);
    char *read_str();
    char **cut_str(char []);
    void print_vector(vector *);

    void convert_to_float_num(float *, char []);
    void *sum_float(void *, void *);
    void *multip_float(void *, void *);



    vector *create_vector(int n, int el_size){
        vector *vec = (vector *)malloc(sizeof(vector));
        vec->size = n;
        vec->element_size = el_size;
        vec->data = malloc(n * el_size);
    }


    vector  *set_vector(int n, int el_size){
        char *user_input = read_str();
        char *buff_s;
        float *buff_f = (float *)malloc(sizeof(float));
        complex *buff_c = (complex *)malloc(sizeof(complex));
        char **cut_user_input = cut_str(user_input);
        vector *vec = create_vector(n, el_size);
        for (int i = 0; i < n; ++i){
            buff_s = cut_user_input[i];
            if (el_size == sizeof(float)){
                convert_to_float_num(buff_f, buff_s);
                set_element(vec, buff_f, i);
            }
            else if (el_size == sizeof(complex)){
                convert_to_complex_num(&buff_c, buff_s);
                set_element(vec, buff_c, i);
            }
        }
        return vec;
    }


    void set_element(vector *vec, void *val, int i){
        void *p_buff = (char *)vec->data + i * vec->element_size;
        memcpy(p_buff, val, vec->element_size);
    }

    void *get_element(vector *vec, int i){
        return (char *)vec->data + i * vec->element_size;
    }

    vector *sum_vector(vector *vec1, vector *vec2, void *(*sum)(void *, void *)){
        int n = vec1->size;
        int el_size = vec1->element_size;
        vector *vec3 = create_vector(n, el_size);
        for (int i = 0; i < n; ++i){
            set_element(vec3, sum(get_element(vec1, i), get_element(vec2, i)), i);
        }
        return vec3;
    }


    void *scalar_multip_vector(vector *vec1, vector*vec2, void *(*multip)(void *, void *), void *(*sum)(void *, void *)){
        void *buff = multip(get_element(vec1, 0), get_element(vec2, 0));
        int n = vec1->size;
        for (int i = 1; i < n; ++i){
            buff = sum(buff, multip(get_element(vec1, i), get_element(vec2, i)));
        }
        return buff;
    }


    void print_vector(vector *vec){
        int n = vec->size;
        int el_size = vec->element_size;
        if (el_size == sizeof(float)) {
            printf("[");
            for (int i = 0; i < n; ++i) {
                if (i == n - 1) {
                    printf("%.2f]\n", *(float *) get_element(vec, i));
                } else {
                    printf("%.2f, ", *(float *) get_element(vec, i));
                }
            }
        }
        else if (el_size == sizeof(complex)){
            printf("[");
            for (int i = 0; i < n; ++i) {
                if (i == n - 1) {
                    printf("%.2f+i*(%.2f)]\n", ((complex *)get_element(vec, i))->re, ((complex *)get_element(vec, i))->im);
                } else {
                    printf("%.2f+i*(%.2f), ", ((complex *)get_element(vec, i))->re, ((complex *)get_element(vec, i))->im);
                }
            }
        }
    }


    void create_complex_num(complex **cmpl, float re_num, float im_num){
        complex *tmp;
        tmp = (complex *)malloc(sizeof(complex));
        tmp->re = re_num;
        tmp->im = im_num;
        *cmpl = tmp;
    }

    void *sum_float(void *v_a, void *v_b){
        float *a = (float *)v_a;
        float *b = (float *)v_b;
        float *c = malloc(sizeof(float));
        *c = *a + *b;
        return c;
    }

    void *multip_float(void *v_a, void *v_b){
        float *a = (float *)v_a;
        float *b = (float *)v_b;
        float *c = malloc(sizeof(float));
        *c = *a * *b;
        return c;
    }

    int len_c(char s[]){
        int i = 0;
        while (s[i] != '\0'){
            ++i;
        }
        return i;
    }

    void *sum_complex(void *v_a, void *v_b){
        complex *a = (complex *)v_a;
        complex *b = (complex *)v_b;
        complex *c;
        create_complex_num(&c, 0.0f, 0.0f);
        c->re = a->re + b->re;
        c->im = a->im + b->im;
        return c;
    }

    void *multip_complex(void *v_a, void *v_b){
        complex *a = (complex *)v_a;
        complex *b = (complex *)v_b;
        complex *c;
        create_complex_num(&c, 0.0f, 0.0f);
        c->re = (a->re * b->re - a->im * b->im);
        c->im = (a->re * b->im + a->im * b->re);
        return c;
    }

    void convert_to_complex_num(complex **c, char input[]){
        int i = 0;
        float sgn_re, sgn_im;
        char *buffs = (char *)malloc(0 * sizeof(char));
        int i_re, f_re, i_im, f_im, j;
        sgn_re = (input[0] == '-' ? -1.0f : 1.0f);
        int u = (sgn_re == -1.0f ? 1 : 0);
        i += u;
        while (input[i] != '.'){
            buffs = (char *)realloc(buffs,(i - u + 1) * sizeof(char));
            buffs[i - u] = input[i];
            ++i;
        }
        buffs = (char *)realloc(buffs,(i - u) * sizeof(char));
        buffs[i - u] = '\0';
        i_re = to_int(buffs);
        free(buffs);
        buffs = (char *)malloc(0 * sizeof(char));
        j = 0;
        ++i;

        while((input[i] != '+') && (input[i] != '-')){
            buffs = (char *)realloc(buffs,(j + 1) * sizeof(char));
            buffs[j] = input[i];
            ++i;
            ++j;
        }
        buffs = (char *)realloc(buffs,(j) * sizeof(char));
        buffs[j] = '\0';
        f_re = to_int(buffs);
        free(buffs);
        sgn_im = (input[i] == '-' ? -1.0f : 1.0f);
        i += 3;
        j = 0;
        buffs = (char *)malloc(0 * sizeof(char));
        while(input[i] != '.'){
            buffs = (char *)realloc(buffs,(j + 1) * sizeof(char));
            buffs[j] = input[i];
            ++i;
            ++j;
        }
        buffs = (char *)realloc(buffs,(j) * sizeof(char));
        buffs[j] = '\0';
        i_im = to_int(buffs);
        free(buffs);
        buffs = (char *)malloc(0 * sizeof(char));
        j = 0;
        ++i;
        while(input[i] != '\0'){
            buffs = (char *)realloc(buffs,(j + 1) * sizeof(char));
            buffs[j] = input[i];
            ++i;
            ++j;
        }
        buffs = (char *)realloc(buffs,(j) * sizeof(char));
        buffs[j] = '\0';
        f_im = to_int(buffs);
        free(buffs);
        create_complex_num(c, sgn_re * ((float)i_re + (float)f_re / (float)power(10, len_i(f_re))), sgn_im * ((float)i_im + (float)f_im / (float)power(10, len_i(f_im))));
    }


    int to_int(char s[]){
        int l = len_c(s), i = 0, ans = 0;
        while (s[i] != '\0'){
            ans += (int)(s[i] - '0') * power(10, l - 1);
            --l;
            ++i;
        }
        return ans;
    }

    int power(int x, int y){
        int i = 0, ans = 1;
        for (i; i < y; ++i){
            ans *= x;
        }
        return ans;
    }

    int len_i(int x){
        int ans = 0;
        ans = (x == 0 ? 1 : ans);
        while (x > 0){
            x /= 10;
            ++ans;
        }
        return ans;
    }

    char *read_str(){
        int c, i = 0;
        char *s = (char *)malloc(0 * sizeof(char));
        while ((c = getchar()) != '\n'){
            s = (char *)realloc(s, (i + 1) * sizeof(char));
            s[i] = (char)c;
            ++i;
        }
        s = (char *)realloc(s, i  * sizeof(char));
        s[i] = '\0';
        return s;
    }

    char **cut_str(char s[]){
        char **cs = (char **)malloc(0 * sizeof(char *));
        char *buffs = (char *)malloc(0 * sizeof(char));
        int i = 0, k = 0, t =0;
        while(s[i] != '\0'){
            if (s[i] == ' '){
                buffs = (char *)realloc(buffs, k * sizeof(char));
                buffs[k] = '\0';
                k = 0;
                cs = (char **)realloc(cs, (t + 1) * sizeof(char *));
                cs[t] = buffs;
                buffs = (char *)malloc(0 * sizeof(char));
                ++t;
                ++i;
            }
            buffs = (char *)realloc(buffs, (k + 1) * sizeof(char));
            buffs[k] = s[i];
            ++k;
            ++i;
        }
        buffs = (char *)realloc(buffs, k * sizeof(char));
        buffs[k] = '\0';
        cs = (char **)realloc(cs, (t + 1) * sizeof(char *));
        cs[t] = buffs;
        return cs;
    }

    void convert_to_float_num(float *x, char input[]){
        int i = 0;
        float sgn = (input[0] == '-' ? -1.0f : 1.0f);
        int c = (sgn == -1.0f ? 1 : 0);
        int i_num, f_num, j;
        float num;
        char *buffs = NULL;
        i += c;
        while (input[i] != '.'){
            buffs = (char *)realloc(buffs,(i - c + 1) * sizeof(char));
            buffs[i - c] = input[i];
            ++i;
        }
        i_num = to_int(buffs);
        free(buffs);
        buffs = (char *)malloc(0 * sizeof(char));
        j = 0;
        ++i;
        while(input[i] != '\0'){
            buffs = (char *)realloc(buffs,(j + 1) * sizeof(char));
            buffs[j] = input[i];
            ++i;
            ++j;
        }
        f_num = to_int(buffs);
        free(buffs);
        num = (float)i_num + ((float)f_num / (float)power(10, len_i(f_num)));
        *x = num * sgn;
    }

#endif
