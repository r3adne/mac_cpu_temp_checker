#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "smc.h"


int amisudoer()
{
    FILE* p_f;
    char anytexthere[8];

    p_f = popen("groups | grep \"wheel\"", "r");

    if (p_f == NULL) { pclose(p_f); return 0; }
    
    if (fgets(anytexthere, sizeof(anytexthere), p_f) != NULL)
    {
        if (anytexthere[0] == 'w') { pclose(p_f); return 1; }
    }

    pclose(p_f);

    return 0;


}

void callPowerMetrics(int hr)
{
    if (! amisudoer())
    {
        if (hr) printf("you must have sudo privileges to use powermetrics. try SMC instead.\n");
        return;
    }

    FILE* p_f;
    char text[128];

    p_f = popen("sudo powermetrics --samplers smc |grep -i \"CPU die temperature\"", "r");

    if (p_f == NULL) { pclose(p_f); return; }

    if (fgets(text , sizeof(text), p_f) != NULL)
    {
        printf("%s", text);
    }

    pclose(p_f);
    printf("\n");
    return;
}

void callSMC(int hr)
{
    printf("%f\n", getSmcValue("TC0P"));
}



int main(int argc, char** argv)
{
    int powermetricsflag = 0;
    int smcflag = 0;
    int shouldmakehumanreadable = 1;
    int sudoinfo = 0;

    while(1)
    {
        int c = getopt(argc, argv, "psanih");
        if (c == -1) break;

        switch (c)
        {
            case 'p':
                powermetricsflag = 1;
                break;
            case 's':
                smcflag = 1;
                break;
            case 'a':
                smcflag = 1; 
                powermetricsflag = 1;
                break;
            case 'n':
                shouldmakehumanreadable = 0;
                break;
            case 'i':
                sudoinfo = 1;
                break;
            case 'h':
                printf("This is a tool to get the current cpu temperature from the cli in macos. Use -p for powermetrics (note: requires sudo), -s for smc, and -a for both. use -n for non-human-readable outputs. Use -i to determine whether or not you are have sudo access.\n");
                return 0;
                break;
        }
    }

    if (sudoinfo)
    {
        int amisudo = amisudoer();
        if (shouldmakehumanreadable) printf(amisudo ? "You are sudoer\n" : "You are not sudoer\n");
        else printf("%i", amisudo);

    }

    if (powermetricsflag) { callPowerMetrics(shouldmakehumanreadable); };
    if (smcflag) { callSMC(shouldmakehumanreadable); };

    return 0;
}
