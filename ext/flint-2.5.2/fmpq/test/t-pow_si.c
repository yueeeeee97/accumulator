/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2009 William Hart
    Copyright (C) 2011 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "long_extras.h"
#include "ulong_extras.h"
#include "fmpq.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("pow_si....");
    fflush(stdout);

    

    /* Check aliasing of a and b */
    for (i = 0; i < 100000; i++)
    {
        fmpq_t a, b, c;
        slong e;

        fmpq_init(a);
        fmpq_init(b);
        fmpq_init(c);

        fmpq_randtest(a, state, 100);
        fmpq_set(b, a);

        e = z_randint(state, 20);

        fmpq_pow_si(c, b, e);
        fmpq_pow_si(b, b, e);

        result = fmpq_equal(b, c);
        if (!result)
        {
            flint_printf("FAIL:\n");
            flint_printf("a = "), fmpq_print(a), flint_printf("\n\n");
            flint_printf("b = "), fmpq_print(b), flint_printf("\n\n");
            flint_printf("c = "), fmpq_print(c), flint_printf("\n\n");
            flint_printf("e = %wd\n", e);
            abort();
        }

        fmpq_clear(a);
        fmpq_clear(b);
        fmpq_clear(c);
    }

    /* Compare with repeated multiplication */
    for (i = 0; i < 10000; i++)
    {
        fmpq_t a, b, c;
        slong j, e;

        fmpq_init(a);
        fmpq_init(b);
        fmpq_init(c);

        fmpq_randtest(a, state, 50);

        e = z_randint(state, 20);

        fmpq_pow_si(b, a, e);

        fmpq_one(c);
        for (j = 0; j < FLINT_ABS(e); j++)
            fmpq_mul(c, c, a);
        if (e < 0)
            fmpq_inv(c, c);

        result = fmpq_equal(b, c);
        if (!result)
        {
            flint_printf("FAIL:\n");
            flint_printf("a = "), fmpq_print(a), flint_printf("\n\n");
            flint_printf("b = "), fmpq_print(b), flint_printf("\n\n");
            flint_printf("c = "), fmpq_print(c), flint_printf("\n\n");
            flint_printf("e = %wd\n", e);
            abort();
        }

        fmpq_clear(a);
        fmpq_clear(b);
        fmpq_clear(c);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}
