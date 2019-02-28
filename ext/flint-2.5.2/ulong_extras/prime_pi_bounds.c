/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License,or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not,write to the Free Software
    Foundation,Inc.,51 Franklin St,Fifth Floor,Boston,MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2009 William Hart
    Copyright (C) 2010, 2013 Fredrik Johansson

******************************************************************************/

#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"

extern const unsigned char FLINT_PRIME_PI_ODD_LOOKUP[];

void n_prime_pi_bounds(ulong *lo, ulong *hi, mp_limb_t n)
{
    if (n < FLINT_PRIME_PI_ODD_LOOKUP_CUTOFF)
    {
        if (n < 3)
            *lo = *hi = (n == 2);
        else
            *lo = *hi = FLINT_PRIME_PI_ODD_LOOKUP[(n-1)/2];
    }
    else
    {
        /* 14/10 < 1/log(2)*/
        *lo = (n / (10 * FLINT_CLOG2(n))) * 14;
        /* 19/10 > 1.25506/log(2) */
        *hi = (n / (10 * FLINT_FLOG2(n)) + 1) * 19;
    }
}

