#include <stdio.h>
#include "tinyexpr.h"

/* An example of calling a C function. */
double my_sum(double a, double b) {
    printf("Called C function with %f and %f.\n", a, b);
    return a + b;
}


int main(int argc, char *argv[])
{
    {
        const char *c = "sqrt(5^2+7^2+11^2+(8-2)^2)";
        double r = te_interp(c, NULL);
        printf("The expression:\n\t%s\nevaluates to:\n\t%f\n", c, r);
    }



    {
        const char *expression = "x*x+y*y";
        printf("Evaluating:\n\t%s\n", expression);

        double x, y;
        te_variable vars[] = {{"x", &x}, {"y", &y}};

        /* This will compile the expression and check for errors. */
        int err;
        te_expr *n = te_compile(expression, vars, 2, &err);

        if (n) {
            /* The variables can be changed here, and eval can be called as many
         * times as you like. This is fairly efficient because the parsing has
         * already been done. */
            x = 3; y = 4;
            const double r = te_eval(n); printf("Result:\n\t%f\n", r);

            te_free(n);
        } else {
            /* Show the user where the error is at. */
            printf("\t%*s^\nError near here", err-1, "");
        }
    }

    {
        double x = 5;
        double y = 6;

        te_variable vars[] = {
            {"x", &x},
            {"y", &y},
            {"mysum", my_sum, TE_FUNCTION2},//TE_FUNCTION2，函数两个输入变量
        };

        const char *expression = "mysum(x, y)";
        printf("Evaluating:\n\t%s\n", expression);

        int err;
        te_expr *n = te_compile(expression, vars, 3, &err);

        if (n) {
            const double r = te_eval(n);
            printf("Result:\n\t%f\n", r);
            te_free(n);
        } else {
            /* Show the user where the error is at. */
            printf("\t%*s^\nError near here", err-1, "");
        }
    }



    return 0;
}
