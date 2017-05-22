//
// Created by Hash Skyd on 5/21/2017.
//

#include "Maket.h"

int afiche_meni_pwodwi() {
    return MM_AKEY;
}

void kreye_paj_pwodwi(Paj * paj)  {
    paj->id = MM_MENI_PWODWI;
    paj->afiche = afiche_meni_pwodwi;
}

