#include "./header/fraction.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "header/algebra.h"

Fraction* new_fraction(int numerator, int denominator)
{
    Fraction* frac = (Fraction*)malloc(sizeof(Fraction));

    if (frac != NULL) 
    {
        if (denominator < 0)
        {
            denominator *= -1;
            numerator *= -1;
        }

        frac->numerator = numerator;
        frac->denominator = denominator != 0 ? denominator : 1;
    }

    return frac;
}

Fraction* new_fraction_num(int numerator)
{
    return new_fraction(numerator, 1);
}

Fraction* new_fraction_default()
{
    return new_fraction_num(0);
}

Fraction* new_fraction_str(const char* str)
{
    int numerator = 1, denominator = 1;

    bool is_frac = false;
    for (int i = 0; i < strlen(str); i++)
        if (str[i] == '/') {
            is_frac = true;
            // numerator
            char * n_c = malloc(i+1);
            for (int j = 0; j < i; j++)
                n_c[j] = str[j];

            sscanf(n_c, "%d", &numerator);
            free(n_c);

            //denominator
            char * d_c = malloc(strlen(str)-(i+1));
            for (int j = 0; j < strlen(str); j++)
                d_c[j] = str[j + i+1];

            sscanf(d_c, "%d", &denominator);
            free(d_c);
            break;
        }

    if (!is_frac){
        sscanf(str, "%d", &numerator);
    }

    return new_fraction(numerator, denominator);
}

Fraction* copy_fraction(Fraction* frac)
{
    return new_fraction(frac->numerator, frac->denominator);
}

Fraction* cut_fraction(Fraction* frac)
{
    if (frac->denominator < 0)
    {
        frac->numerator *= -1;
        frac->denominator *= -1;
    }

    int gcd = nod(frac->numerator, frac->denominator);

    frac->numerator /= gcd;
    frac->denominator /= gcd;

    frac->denominator = frac->denominator != 0 ? frac->denominator : 1;

    return frac;
}

Fraction* neg_fraction(Fraction* frac)
{
    frac->numerator *= -1;

    return frac;
}

Fraction* pow_fraction(Fraction* frac, int exp)
{
    frac->numerator = powi(frac->numerator, exp);
    frac->denominator = powi(frac->denominator, exp);

    return cut_fraction(frac);
}

Fraction* inv_fraction(Fraction* frac)
{
    int tmp = frac->numerator;
    frac->numerator = frac->denominator;
    frac->denominator = tmp;

    return frac;
}

double result_fraction(Fraction* frac)
{
    double res = (double)frac->numerator / (double)frac->denominator;
    destroy_fraction(frac);
    return res;
}

int get_numerator_fraction(Fraction* frac)
{
    return frac->numerator;
}

int get_denominator_fraction(Fraction* frac)
{
    return frac->denominator;
}

void set_fraction(Fraction* old_frack, Fraction* new_frack)
{
    destroy_fraction(old_frack);
    old_frack = copy_fraction(new_frack);
    destroy_fraction(new_frack);
}

bool is_zero_fraction(Fraction* frac)
{
    bool res = frac->numerator == 0 ? true : false;
    destroy_fraction(frac);
    return res;
}

void destroy_fraction(Fraction* frac)
{
    if (frac != NULL) free(frac);
}

void print_fraction(Fraction* frac)
{
    printf("%d", frac->numerator);
    if (frac->denominator != 1 && frac->numerator != 0) 
        printf("/%d", frac->denominator);
    destroy_fraction(frac);
}

bool is_equal_fraction(Fraction* frac1, Fraction* frac2)
{
    bool res = frac1->numerator*frac2->denominator == frac1->denominator * frac2->numerator;
    destroy_fraction(frac1);
    destroy_fraction(frac2);
    return res;
}

Fraction* add_fraction(Fraction* frac, Fraction* other)
{
    Fraction* frac_res = new_fraction(
            frac->numerator * other->denominator + other->numerator * frac->denominator,
            frac->denominator * other->denominator
            );
    destroy_fraction(frac);
    destroy_fraction(other);
    return cut_fraction(frac_res);
}

Fraction* sub_fraction(Fraction* frac, Fraction* other)
{
    Fraction* frac_res = new_fraction(
            frac->numerator * other->denominator - other->numerator * frac->denominator,
            frac->denominator * other->denominator
            );
    destroy_fraction(frac);
    destroy_fraction(other);
    return cut_fraction(frac_res);
}

Fraction* mul_fraction(Fraction* frac, Fraction* other)
{
    Fraction* frac_res = new_fraction(
            frac->numerator * other->numerator,
            frac->denominator * other->denominator
            );
    destroy_fraction(frac);
    destroy_fraction(other);
    return cut_fraction(frac_res);
}

Fraction* div_fraction(Fraction* frac, Fraction* other)
{
    Fraction* frac_res = new_fraction(
            frac->numerator * other->denominator,
            frac->denominator * other->numerator
            );
    destroy_fraction(frac);
    destroy_fraction(other);
    return cut_fraction(frac_res);
}