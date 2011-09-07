#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { N = 10 };
enum { NumBoard = 20 };

struct Board {
    /* population? */
    int axQueen[N];
    /* gene? */
    int gcode[N];
    float rFitness;
} Board;

struct Board aboard[NumBoard];
int mdata[20],crossdata[10][2];

int nCrossoverRatio;
int nMutationRatio;
int nMaxGeneration;

FILE * pfileMax;
FILE * pfileMin;
FILE * pfileAve;

int nowno(int,int);
void showBoard(int);
void ga_init(void);
void ga_loop(void);
float calcFitness(int);
int cross(int);
void printpcode(int);
void printgcode(int);
void printfit(int);
void ptog(int);
void gtop(int);
void ga_eval(int);
void ga_select(void);
void ga_cross_over(void);
void analy(void);
void ga_mutate(void);

static void
usage (
  const char * pszCmdName,
  const char * pszErrorMessage ) {
    if (pszErrorMessage) {
        fprintf(stderr, "Error: %s\n", pszErrorMessage);
    }
    fprintf(stderr, "Usage: %s CROSSOVER_RATIO " \
     "MUTATION_RATIO MAX_GENERATION\n", pszCmdName );
    fprintf(stderr, "  CROSSOVER_RATIO = 0 - 100\n");
    fprintf(stderr, "  MUTATION_RATIO  = 0 - 100\n");
    fprintf(stderr, "  MAX_GENERATION  = 1 - Inf\n");
}

int
main(
  int argc,
  char * * argv ) {
    nCrossoverRatio = atoi(argv[1]);
    if (nCrossoverRatio < 0 || 100 < nCrossoverRatio) {
        usage(argv[0], "Crossover ratio out of range.");
        exit(1);
    }
    nMutationRatio = atoi(argv[2]);
    if(nMutationRatio < 0 || 100 < nMutationRatio) {
        usage(argv[0], "Mutation ratio out of range.");
        exit(1);
    }
    nMaxGeneration = atoi(argv[3]);
    if (nMaxGeneration <1) {
        usage(argv[0], "Maximum generation must be greater than 0.");
        exit(1);
    }
    /* ------------------------------------------------------------ */
    pfileMax = fopen("max.dat", "w");
    fprintf(pfileMax, "TitleText: NQUEEN_MAX(%d, %d)\n", nCrossoverRatio, 
     nMutationRatio );
    fprintf(pfileMax, "XUnitText: Generation\n");
    fprintf(pfileMax, "YUnitText: RFitness\n");
    fprintf(pfileMax, "\"MaxFitness\n");
    /* ------------------------------------------------------------ */
    pfileMin=fopen("min.dat", "w");
    fprintf(pfileMin, "TitleText: NQUEEN_MIN(%d, %d)\n", nCrossoverRatio, 
     nMutationRatio );
    fprintf(pfileMin, "XUnitText: Generation\n");
    fprintf(pfileMin, "YUnitText: RFitness\n");
    fprintf(pfileMin, "\"MinFitness\n");
    /* ------------------------------------------------------------ */
    pfileAve=fopen("ave.dat", "w");
    fprintf(pfileAve, "TitleText: NQUEEN_AVE(%d, %d)\n", nCrossoverRatio, 
     nMutationRatio );
    fprintf(pfileAve, "XUnitText: Generation\n");
    fprintf(pfileAve, "YUnitText: RFitness\n");
    fprintf(pfileAve, "\"FitnessAVE\n");
    /* ------------------------------------------------------------ */
    ga_init();
    ga_loop();
    fclose(pfileMax);
    fclose(pfileMin);
    fclose(pfileAve);
    return (0);
}

void
ga_init() {
  int axQueen[N];
  int y;
  int y1;
  int y2;
  int x;
  int yEnd;
  int iBoard;
  time_t time1;
    for(y = 0, x = 0; y < N; y ++, x ++) {
        axQueen[y] = y + 1;
    }
    time(& time1);
    srand((unsigned int) time1);
    for (iBoard = 0; iBoard < NumBoard; iBoard ++) {
        y1 = 0;
        y2 = y1 + 1;
        yEnd = rand() % N;
        for (y = 0; y < yEnd; y ++) {
            x = axQueen[y1];
            axQueen[y1] = axQueen[y2];
            axQueen[y2] = x;
            if (y1 == N - 2) {
                y1 = 0;
                y2 = y1 + 1;
            }  else {
                y1 = y1 + 1;
                y2 = y1 + 1;
            }
        }
        for (y = 0; y < N; y ++) {
            aboard[iBoard].axQueen[y] = axQueen[y];
        }
        aboard[iBoard].rFitness = calcFitness(iBoard);
        ptog(iBoard);
    }
}
void
ga_loop() {
  int iGeneration;
    for(iGeneration = 0; iGeneration <= nMaxGeneration; iGeneration ++) {
        ga_eval(iGeneration);
        ga_select();
        ga_cross_over();
        ga_mutate();
        analy();
    }
    printf("Failing !!\n");
}

float
calcFitness(int iBoard) {
  int cpoint;
  float ans; 
    cpoint = cross(iBoard);
    ans = 1 / (1 + ((float) cpoint));
    return (ans);
}

int
cross (
  int iBoard ) {
  int i,j,count;
  int up,down,sub;
  count = 0;
  for (i = 0; i < 9; i ++) {
      for(j=i+1;j<10;j++)
        {
          sub=j-i;
          up=aboard[iBoard].axQueen[i]-sub;
          down=aboard[iBoard].axQueen[i]+sub;
          if(up == aboard[iBoard].axQueen[j] || down == aboard[iBoard].axQueen[j])
            {
              count ++;
            }
        }
    }
  return(count);
}
void printpcode(int iBoard)
{
  int i;
  for(i=0;i<10;i++)
    {
      printf("%3d ",aboard[iBoard].axQueen[i]);
    }
  printf("\n");
}
void printfit(int iBoard)
{
  printf("IBoard.%d rFitness = %f\n",iBoard,aboard[iBoard].rFitness);
}

void printgcode (
  int iBoard ) {
  int i;
  for(i=0;i<10;i++)
    printf("%3d ",aboard[iBoard].gcode[i]);
  printf("\n");
}

void
ptog (
  int iBoard ) {
  int i,j,k,s[10];
    for (i = 0; i < 10; i ++) {
        s[i] = i + 1;
    }
    for (i = 0; i < 10; i ++) {
        j=0;
        while (aboard[iBoard].axQueen[i] != s[j]) {
            j ++;
        }
        aboard[iBoard].gcode[i] = j;
        for (k = j; k < 9; k ++) {
            s[k]=s[k+1];
        }
        s[9] = -1;
    }
}

void
ga_select () {
  int iBoard,j,point,kk,k;
  time_t time1;
    time(& time1);
    srand((unsigned int) time1);
    for (iBoard = 0; iBoard < N; iBoard ++) {
        for(j = 0; j < 2; j ++) {
            point = rand() % mdata[N - 1];
            kk=0;
            for(k=0;k<20;k++) {
                if (mdata[k] < point) {
                    kk ++;
                }
            }
            crossdata[iBoard][j]=kk;
        }
    }
}

void
ga_eval (
  int iGeneration ) {
  float rFitnessMax;
  float rFitnessMin;
  float rSumOfFitness;
  float rAverageOfFitness;
  int iBoard;
  int iBoardOfMax;
  int iBoardOfMin;
    rFitnessMin = 1.0;
    iBoardOfMax=0;
    iBoardOfMin=-1;
    rSumOfFitness=rFitnessMax=0.0;
    for (iBoard = 0; iBoard < NumBoard; iBoard ++) {
        if (aboard[iBoard].rFitness > rFitnessMax) {
            rFitnessMax = aboard[iBoard].rFitness;
            iBoardOfMax = iBoard;
        }
        if (rFitnessMin >= aboard[iBoard].rFitness) {
            rFitnessMin=aboard[iBoard].rFitness;
            iBoardOfMin=iBoard;
        }
        rSumOfFitness = rSumOfFitness + aboard[iBoard].rFitness;
    }
    printf("%d th generation\n",iGeneration);
#if 0
    printf("queen pattern\n");
    for(iBoard = 0; iBoard < NumBoard; iBoard ++) {
        printf("%2d:", iBoard);
        for(y = 0; y < N; y ++) {
            printf(" %3d", aboard[iBoard].axQueen[y]);
        }
        printf("\n");
    }
    printf("gcode\n");
    for (iBoard = 0; iBoard < NumBoard; iBoard ++) {
        printf("%2d:", iBoard);
        for(y = 0; y < N; y ++) {
            printf(" %3d", aboard[iBoard].gcode[y]);
        }
        printf("\n");
    }
#endif
    rAverageOfFitness = rSumOfFitness / NumBoard;
    printf("board %d has the maximum fitness %f.\n", iBoardOfMax,
     rFitnessMax );
    printf("board %d has the minimum fitness %f.\n", iBoardOfMin,
     rFitnessMin );
    printf("average of fitness is %f\n", rAverageOfFitness);
    fprintf(pfileMax,"%d %f\n", iGeneration, rFitnessMax);
    fprintf(pfileMin,"%d %f\n", iGeneration, rFitnessMin);
    fprintf(pfileAve,"%d %f\n", iGeneration, rAverageOfFitness);
    if (rFitnessMax == 1.0) {
        printf("A solution appeared in the %dth generation.\n",
         iGeneration );
        showBoard(iBoardOfMax);
        fclose(pfileMax);
        fclose(pfileMin);
        fclose(pfileAve);
        exit(0);
    }
    mdata[0] = (int) (aboard[0].rFitness * N * 1000 / rSumOfFitness);
    for (iBoard = 1; iBoard < NumBoard; iBoard ++){
        mdata[iBoard] = mdata[iBoard - 1] +
         (int) (aboard[iBoard].rFitness * N * 1000 / rSumOfFitness);
    }
}

void
ga_cross_over () {
  float crossp;
  int line,point,gline;
  int i,j,k,gcopy[2][10],gcopy2[20][10];
  time_t time1;
  crossp=(float)nCrossoverRatio/100.0;
  time(& time1);
  srand((unsigned int) time1);
  line =(int)(crossp * 1000);
  for(i=0;i<10;i++)
    {
      point = rand() % 1000;
      if(point < line)
        /**  in case of bingo  **/
        {
          gline = rand() % 9;
          for(j=0;j<gline;j++)
            {
              gcopy[0][j]=aboard[crossdata[i][0]].gcode[j];
              gcopy[1][j]=aboard[crossdata[i][1]].gcode[j];
            }
          for(j=gline;j<10;j++)
            {
              gcopy[0][j]=aboard[crossdata[i][1]].gcode[j];
              gcopy[1][j]=aboard[crossdata[i][0]].gcode[j];
            }
          for(j=0;j<10;j++)
            {
              for(k=0;k<10;k++)
                {
                  gcopy2[i*2][k]=gcopy[0][k];
                  gcopy2[i*2+1][k]=gcopy[1][k];
                }
            }
        }
      else
        {
          for(j=0;j<10;j++)
            {
              for(k=0;k<10;k++)
                {
                  gcopy2[i*2][k]=aboard[crossdata[i][0]].gcode[k];
                  gcopy2[i*2+1][k]=aboard[crossdata[i][1]].gcode[k];
                }
            }
        }
    }
  for(i=0;i<20;i++)
    {
      for(j=0;j<10;j++)
        {
          aboard[i].gcode[j]=gcopy2[i][j];
        }
    }
}

void
analy() {
  int i;
  for(i=0;i<20;i++)
    {
      gtop(i);
      aboard[i].rFitness=calcFitness(i);
    }
}

void
gtop (
  int iBoard ) {
  int i,j;
  int s[10],ss;
  for(i=0;i<10;i++)
    s[i]=i+1;
  for(i=0;i<10;i++)
    {
      ss = aboard[iBoard].gcode[i];
      aboard[iBoard].axQueen[i]=s[ss];
      for(j=ss;j<9;j++)s[j]=s[j+1];
      s[9]=-1;
    }
}

void
ga_mutate () {
  int i,j,line,point,nno;
  float changep;
  time_t time1;
  changep=(float)nMutationRatio / 100.0;
  time(& time1);
  srand((unsigned int) time1);
  line = (int)( changep * 1000);
  for(i=0;i<20;i++)
    {
      for(j=0;j<10;j++)
        {
          point = rand() % 1000;
          if(point < line)
            {
              nno = nowno(j,aboard[i].gcode[j]);
              aboard[i].gcode[j] = nno;  
            }
        }
    }
}

int
nowno (
  int posi,
  int now ) {
  int ans,limit;
  time_t time1;
  time(& time1);
  srand((unsigned int) time1);
  ans = now;
  if(posi == 9)
    ans=0;
  else
    {
      limit = 10 - posi;
      while(ans == now)
        {
          ans = rand() % limit; 
        }
    }
  return(ans);
}

void
showBoard (
  int iBoard ) {
  int y,x;
    printf("board %d\n", iBoard);
    for(y = 0; y < N; y ++) {
        for (x = 0; x < N; x ++) {
            if (x == aboard[iBoard].axQueen[y] - 1) {
                printf(" Q");
            } else {
                printf(" -");
            }
        }
        printf("\n");
    }
}
