#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

typedef struct bats
{  float strike_rate,runs_scored;
    int count, pos, change,out, ball_faced, fours, sixes, two, ones, threes;} bt;

typedef struct bowls
{  
     int overs, runs_conceded, economy, nb, wd, maiden, wickets;} bl;

typedef struct extras
{ int wd,n,b,lb; }ex;

typedef struct wckt
{
    char wicket[100],caught[3],bowled[3],hit[12],stumped[3],lbw[5],run_out[10];

    int wicket_type;
    
}wckts;

typedef struct players
{   char player_name[20];
    char role[10];
} pl;

typedef struct lengths
{    int team_l[2], date_l, overs_l, m_time_l, venue_l, umpire_l, w_toss_l, l_toss_l, pl_length[2][11],wicket_str_l[2][11];} l;

void runs_checker(int i, int j, int st[2],int n_st[2], int* pl1, int* pl2,int* pos, int* total,ex extra[2] ,pl b_o[2][11], int batting,int* wicket,char wk[], int fielding, int bowler_no, bt batsmen[2][11], bl bowlers[2][11],int this_over[],int overs,char runs[2][overs][6],char* runs_po[2][overs][13],char wicket_str[11][100],pl t_player[2][11],int over_extra[overs],int k[1])
{
    fflush(stdin);
    k[0]++;
    printf("\n\e[31;1mRun\e[0m : ");
    scanf("%c", &runs[batting][i][k[0]]);
    fflush(stdin);
    runs_po[batting][i][k[0]]=&runs[batting][i][k[0]];
    
    batsmen[batting][*pos].ball_faced += 1;
   
    if (*runs_po[batting][i][k[0]] == '0')
    {
        printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,no run", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
        batsmen[batting][*pos].runs_scored += 0;
       
    }
    else if (*runs_po[batting][i][k[0]] == '1')
    {  batsmen[batting][*pos].ones++;
       bowlers[fielding][bowler_no-1].runs_conceded+=1;
       batsmen[batting][*pos].runs_scored += 1;
       *total +=  1; this_over[i]+=1;
        batsmen[batting][*pos].strike_rate=(batsmen[batting][*pos].runs_scored/batsmen[batting][*pos].ball_faced)*100;
    
        if (batsmen[batting][0].count==0 && (*pos==n_st[batting]))
        {
            printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m, %c run", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name, *runs_po[batting][i][k[0]]);
            *pos-=1;
            batsmen[batting][0].count+=1;
            *pos=st[batting];
          
        }
         else if (batsmen[batting][0].count==1  && (*pos==st[batting]))
        {
            printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m, %c run", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name, *runs_po[batting][i][k[0]]);
           *pos+=1;
            batsmen[batting][0].count-=1;
            *pos=n_st[batting];
            
           
        }
        
    }
    else if (*runs_po[batting][i][k[0]] == '2')
    {
        printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m, %c runs", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name, *runs_po[batting][i][k[0]]);
        batsmen[batting][*pos].runs_scored += 2;
        
        batsmen[batting][*pos].two++;
        bowlers[fielding][bowler_no-1].runs_conceded+=2;
        *total +=  2; this_over[i]+=2; 
        batsmen[batting][*pos].strike_rate=(batsmen[batting][*pos].runs_scored/batsmen[batting][*pos].ball_faced)*100; 
       
    }
    else if (*runs_po[batting][i][k[0]] == '3')
    {
        batsmen[batting][*pos].threes++;
        batsmen[batting][*pos].runs_scored += 3;
        
        bowlers[fielding][bowler_no-1].runs_conceded+=3;
            *total +=  3; this_over[i]+=3; 
             batsmen[batting][*pos].strike_rate=(batsmen[batting][*pos].runs_scored/batsmen[batting][*pos].ball_faced)*100; 
            
        if (batsmen[batting][0].count==0 && (*pos==n_st[batting]))
        {
            printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m, %c runs", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name, *runs_po[batting][i][k[0]]);
            *pos-=1;
            batsmen[batting][0].count+=1;
            *pos=st[batting];
           
        }
        else if (batsmen[batting][0].count==1  && (*pos==st[batting]))
        {
            printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m, %c runs", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name, *runs_po[batting][i][k[0]]);
           *pos+=1;
            batsmen[batting][0].count-=1;
            *pos=n_st[batting];
          
        }    
    }   
    else if (*runs_po[batting][i][k[0]] == '4')
    {
        printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m, FOUR, Down the ground good shot by %s", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name, b_o[batting][*pos].player_name);
        batsmen[batting][*pos].runs_scored += 4;
        batsmen[batting][*pos].fours++;
        bowlers[fielding][bowler_no-1].runs_conceded+=4;
        *total +=  4;
        this_over[i]+=4;
         batsmen[batting][*pos].strike_rate=(batsmen[batting][*pos].runs_scored/batsmen[batting][*pos].ball_faced)*100; 
       
    }
    else if (*runs_po[batting][i][k[0]] == '6')
    {
        printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m, HURRAY....!!! its SIX, What a shot by %s", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name, b_o[batting][*pos].player_name);
        batsmen[batting][*pos].runs_scored += 6;
        
        bowlers[fielding][bowler_no-1].runs_conceded+=6;
        *total +=  6;
        this_over[i]+=6;
        batsmen[batting][*pos].sixes++;
         batsmen[batting][*pos].strike_rate=(batsmen[batting][*pos].runs_scored/batsmen[batting][*pos].ball_faced)*100; 
       
    }
    else if (*runs_po[batting][i][k[0]] == 'w' || *runs_po[batting][i][k[0]] == 'W')
    {
         batsmen[batting][*pos].strike_rate=(batsmen[batting][*pos].runs_scored/batsmen[batting][*pos].ball_faced)*100; 
        *wicket=*wicket + 1;
         char caught[5]={"c "},bowled[5]={" b "},o_bowled[5]={"b "},stumped[5]={"st "},hit[12]={"hit wicket "},run_out[10]={"run out "},lbw[5]={"lbw "},and[4]={"& "}, open_[3]={"("},close_[3]={")"};

        int wicket_type,player_no;
        
        printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m, OH!!! WICKET %s has to go to the pavilion", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name, b_o[batting][*pos].player_name);
        bowlers[fielding][bowler_no - 1].wickets++;
       printf("\n\n1.Caught\n2.Bowled\n3.Stumped\n4.Hit wicket\n5.Run Out\n6.LBW\n\n");
       printf("Select the option from the above 1..6 : ");
       scanf("%d",&wicket_type);
       
       switch (wicket_type)
       {
       case 1:
           printf("\nCaught by player number from the team : ");
           scanf("%d",&player_no);
           fflush(stdin);
           strcat(wicket_str[*pos],caught);
           if(player_no==bowler_no)
           {
           strcat(wicket_str[*pos],and);
           strcat(wicket_str[*pos],o_bowled);
           }
           else
           {
           strcat(wicket_str[*pos],b_o[fielding][player_no-1].player_name);
           strcat(wicket_str[*pos],bowled);
           }
           strcat(wicket_str[*pos],b_o[fielding][bowler_no-1].player_name);
           break;
        case 2:
            
           strcat(wicket_str[*pos],o_bowled);
           strcat(wicket_str[*pos],b_o[fielding][bowler_no-1].player_name);
           break;
        case 3:
           strcat(wicket_str[*pos],stumped);
           strcat(wicket_str[*pos],wk);
           strcat(wicket_str[*pos],bowled);
           strcat(wicket_str[*pos],b_o[fielding][bowler_no-1].player_name);
           break;
        case 4:
           strcat(wicket_str[*pos],hit);
           strcat(wicket_str[*pos],o_bowled);
           strcat(wicket_str[*pos],b_o[fielding][bowler_no-1].player_name);
           break;
        case 5:
            printf("\nRun out by player number from the team : ");
           scanf("%d",&player_no);
           strcat(wicket_str[*pos],run_out);
           strcat(wicket_str[*pos],open_);
           strcat(wicket_str[*pos],b_o[fielding][player_no-1].player_name);
           strcat(wicket_str[*pos],close_);
           
           break;
        case 6:
           strcat(wicket_str[*pos],lbw);
           strcat(wicket_str[*pos],o_bowled);
           strcat(wicket_str[*pos],b_o[fielding][bowler_no-1].player_name);
           break;     
       default:
           break;
       }
       printf("%s to %s, THATS OUT!!!\n", b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
       printf("%s %s  %.f(%d) [4s-%d 6s-%d]\n",b_o[batting][*pos].player_name,wicket_str[*pos],batsmen[batting][*pos].runs_scored,batsmen[batting][*pos].ball_faced,batsmen[batting][*pos].fours,batsmen[batting][*pos].sixes);
       
  
        for(int p=2;p<11;p++)
        {
            if(batsmen[batting][p].out==0 && (*pos==st[batting]))
            {
                batsmen[batting][p].out+=1;
                *pl1=p;
                st[batting]=*pl1;
                *pos=st[batting];
               
                break;
            }
            else if(batsmen[batting][p].out==0 && (*pos==n_st[batting]))
            {
                batsmen[batting][p].out+=1;
                *pl2=p;
                n_st[batting]=*pl2;
                *pos=n_st[batting];
               
                break;
            }
        }
               
       
    }
    else if (*runs_po[batting][i][k[0]] == 'n' || *runs_po[batting][i][k[0]] == 'N')
    {   
        printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,NO BALL,free hit!!!\n", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
        printf("\tIt is really disappointing for the bowler.");
        printf("%s has to bowl again.", b_o[fielding][bowler_no - 1].player_name);
        *total +=  1; this_over[i]+=1;  
        over_extra[i]+=1;
        extra[batting].n+=1;
        batsmen[batting][*pos].ball_faced -= 1;
         batsmen[batting][*pos].strike_rate=(batsmen[batting][*pos].runs_scored/batsmen[batting][*pos].ball_faced)*100; 
       runs_checker(i, j,st,n_st,pl1,pl2,pos, total,extra , b_o, batting,wicket,wk, fielding, bowler_no, batsmen, bowlers,this_over,overs,runs,runs_po,wicket_str,t_player,over_extra,k);
    }
    else if (*runs_po[batting][i][k[0]] == 'b' || *runs_po[batting][i][k[0]] == 'B')
    {
        printf("\nbye runs : ");
       // k[0]++;
        scanf("%c", &runs[batting][i][k[0]]);
        runs_po[batting][i][k[0]]=&runs[batting][i][k[0]];
        fflush(stdin);
       // batsmen[batting][*pos].ball_faced += 1;
         batsmen[batting][*pos].strike_rate=(batsmen[batting][*pos].runs_scored/batsmen[batting][*pos].ball_faced)*100; 
        if (*runs_po[batting][i][k[0]] == '1')
        { *total +=  1; this_over[i]+=1; 
           extra[batting].b+=1;
            over_extra[i]+=1;

           if (batsmen[batting][0].count==0 && (*pos==n_st[batting]))
            {        
                printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,bye,1 run", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
                *pos-=1;
                 batsmen[batting][0].count+=1;
                *pos=st[batting];
                  
            
        }
      
            else if (batsmen[batting][0].count==1  && (*pos==st[batting]))
            {
            
                printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,bye,1 run", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
                *pos+=1;
                batsmen[batting][0].count-=1;
                *pos=n_st[batting];
               
            }
        }
        else if (*runs_po[batting][i][k[0]] == '2')
        {
            printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,byes,2 runs", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
            *total +=  2; this_over[i]+=2;  
            extra[batting].b+=2;
             over_extra[i]+=2;
           
        }
         else if (*runs_po[batting][i][k[0]] == '3')
        {*total +=  3; this_over[i]+=3;
         extra[batting].b+=3;
          over_extra[i]+=3;
            if (batsmen[batting][0].count==0 && (*pos==n_st[batting]))
            {        
                printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,byes,3 runs", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
               *pos-=1;
               batsmen[batting][0].count+=1;
                *pos=st[batting];
                  
            
        }
      
            else if (batsmen[batting][0].count==1  && (*pos==st[batting]))
            {
            
                printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,byes,3 runs", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
                *pos+=1;
                batsmen[batting][0].count-=1;
                *pos=n_st[batting];
               
            }
        }
        else if (*runs_po[batting][i][k[0]] == '4')
        {
            printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,byes,4 runs.\n\tI think bowler would be really dissapointed because of these extra runs", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
            *total +=  4;
            this_over[i]+=4;
            extra[batting].b+=4;
             over_extra[i]+=4;
           
        }
        else
        {
            printf("Invalid input!!!");
             batsmen[batting][*pos].ball_faced -= 1;
             k[0]--;
            runs_checker(i, j,st,n_st,pl1,pl2,pos, total,extra , b_o, batting,wicket,wk, fielding, bowler_no, batsmen, bowlers,this_over,overs,runs,runs_po,wicket_str,t_player,over_extra,k);
        }
    }
    else if (*runs_po[batting][i][k[0]] == 'l' || *runs_po[batting][i][k[0]] == 'L')
    {
       
        printf("\nLeg bye runs : ");
       // k[0]++;
        scanf("%c", &runs[batting][i][k[0]]);
        runs_po[batting][i][k[0]]=&runs[batting][i][k[0]];
        fflush(stdin);
       // batsmen[batting][*pos].ball_faced += 1;
        batsmen[batting][*pos].strike_rate=(batsmen[batting][*pos].runs_scored/batsmen[batting][*pos].ball_faced)*100;
        *total +=  1; this_over[i]+=1; 
        if (*runs_po[batting][i][k[0]] == '1')
        {
            extra[batting].lb+=1; 
             over_extra[i]+=1;
            if (batsmen[batting][0].count==0 && (*pos==n_st[batting]))
            {        
                printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,leg bye,1 run", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
                
                *pos-=1;
                
                batsmen[batting][0].count+=1;
                *pos=st[batting];
            }
      
            else if (batsmen[batting][0].count==1  && (*pos==st[batting]))
            {
            
                printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,leg bye,1 run", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
                *total +=  1; this_over[i]+=1;  
                extra[batting].lb+=1;
                *pos+=1;
                batsmen[batting][0].count-=1;
                *pos=n_st[batting];
               
            }
        }
        else if (*runs_po[batting][i][k[0]] == '2')
        {
            printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,leg byes,2 runs", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
            *total +=  2; this_over[i]+=2;  
            extra[batting].lb+=2;
             over_extra[i]+=2;
           
        }
        else if (*runs_po[batting][i][k[0]] == '3')
        {
           extra[batting].lb+=3;
            over_extra[i]+=3;
           if (batsmen[batting][0].count==0 && (*pos==n_st[batting]))
            {        
                printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,leg byes,3 runs", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
                *total +=  3; this_over[i]+=3;  
                *pos-=1;
                batsmen[batting][0].count+=1;
                *pos=st[batting];
                  
            
        }
      
            else if (batsmen[batting][0].count==1  && (*pos==st[batting]))
            {
            
                printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,leg byes,3 runs", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
                *total +=  3; this_over[i]+=3;  
                *pos+=1;
                batsmen[batting][0].count-=1;
                *pos=n_st[batting];
               
                
            }
        }
        else if (*runs_po[batting][i][k[0]] == '4')
        {
            printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,leg byes,4 runs.\n\tI think bowler would be really dissapointed because of these extra runs", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name);
            *total +=  4;        
            this_over[i]+=4;
            extra[batting].lb+=4;
             over_extra[i]+=4;
           
        }
        else
        {
            printf("Invalid input!!!");
            batsmen[batting][*pos].ball_faced -= 1;
            k[0]--;
            runs_checker(i, j,st,n_st,pl1,pl2,pos, total,extra , b_o, batting,wicket,wk, fielding, bowler_no, batsmen, bowlers,this_over,overs,runs,runs_po,wicket_str,t_player,over_extra,k);
        }
    }
    else if (*runs_po[batting][i][k[0]] == 'd' || *runs_po[batting][i][k[0]] == 'D')
    {
        printf(" %d.%d    \e[32m%s\e[0m to \e[33m%s\e[0m,Wide Ball\n\t%s has to bowl again.", i, j, b_o[fielding][bowler_no - 1].player_name, b_o[batting][*pos].player_name, b_o[fielding][bowler_no - 1].player_name);
        *total +=  1; this_over[i]+=1;   
        extra[batting].wd+=1;
         over_extra[i]+=1;
        batsmen[batting][*pos].ball_faced -= 1;
         batsmen[batting][*pos].strike_rate=(batsmen[batting][*pos].runs_scored/batsmen[batting][*pos].ball_faced)*100; 
       runs_checker(i, j,st,n_st,pl1,pl2,pos, total,extra , b_o, batting,wicket,wk, fielding, bowler_no, batsmen, bowlers,this_over,overs,runs,runs_po,wicket_str,t_player,over_extra,k);
        
    }
    else
    {
        printf("Invalid Input!!");
        batsmen[batting][*pos].ball_faced -= 1;
            k[0]--;
       runs_checker(i, j,st,n_st,pl1,pl2,pos, total,extra , b_o, batting,wicket,wk, fielding, bowler_no, batsmen, bowlers,this_over,overs,runs,runs_po,wicket_str,t_player,over_extra,k);
    }
   
   
}

void matchinfo(char date[], char m_time[], char venue[], char opt, char umpire[], char team[2][35], pl t_player[2][11], pl b_o[2][11], int overs, char w_toss[], char l_toss[], l item, char same[])
{
    int i, j, a, size, num = 0;

    printf(" _______________________________________________________________________________________________\n");
    printf("|                                                                                               |\n");
    printf("|                                       MATCH INFO                                              |\n");
    printf("|_______________________________________________________________________________________________|\n");
    if (overs < 10)
    {
        printf("| Match             %s vs %s,%d overs,2022", team[0], team[1], overs);
        size = 97 - (37 + (item.team_l[0]) + (item.team_l[1]));
    }
    if (overs >= 10 && overs <= 99)
    {
        printf("| Match             %s vs %s,%d overs,2022", team[0], team[1], overs);
        size = 97 - (38 + (item.team_l[0]) + (item.team_l[1]));
    }
    if (overs >= 100)
    {
        printf("| Match             %s vs %s,%d overs,2022", team[0], team[1], overs);
        size = 97 - (39 + (item.team_l[0]) + (item.team_l[1]));
    }

    for (i = 1; i < size; i++)
    {
        printf(" ");
    }
    printf("|\n");
    printf("| Date              %s", date);
    size = 97 - (20 + item.date_l);

    for (i = 1; i < size; i++)
    {
        printf(" ");
    }
    printf("|\n");

    printf("| Toss              %s", w_toss);
    size = 97 - (20 + item.w_toss_l);

    for (i = 1; i < size; i++)
    {
        printf(" ");
    }
    printf("|\n");
    printf("| Time              %s", m_time);
    size = 97 - (20 + item.m_time_l);

    for (i = 1; i < size; i++)
    {
        printf(" ");
    }
    printf("|\n");
    printf("| Venue             %s", venue);
    size = 97 - (20 + item.venue_l);

    for (i = 1; i < size; i++)
    {
        printf(" ");
    }
    printf("|\n");
    printf("| Umpire            %s", umpire);
    size = 97 - (20 + item.umpire_l);

    for (i = 1; i < size; i++)
    {
        printf(" ");
    }
    printf("|\n");
    while (num < 2)
    {
        printf("|                                                                                               |\n");
        printf("| %s Squad", team[num]);
        size = 97 - (8 + item.team_l[num]);

        for (i = 1; i < size; i++)
        {
            printf(" ");
        }
        printf("|\n");
        printf("|                                                                                               |\n");
        if (same[num] == 's')
        {
            printf("| Playing           %s (c & wk)", t_player[num][0].player_name);
            printf(", %s", t_player[num][1].player_name);
        }
        else
        {
            printf("| Playing           %s (c)", t_player[num][0].player_name);
            printf(", %s (wk)", t_player[num][1].player_name);
        }
        for (i = 2; i <= 3; i++)
        {
            printf(", %s", t_player[num][i].player_name);
        }
        size = 97 - (35 + item.pl_length[num][0] + item.pl_length[num][1] + item.pl_length[num][2] + item.pl_length[num][3]);

        for (i = 1; i < size; i++)
        {
            printf(" ");
        }
        printf("|");

        printf("\n|                   %s", t_player[num][4].player_name);
        for (i = 5; i <= 7; i++)
        {
            printf(", %s", t_player[num][i].player_name);
        }
        size = 97 - (26 + item.pl_length[num][4] + item.pl_length[num][5] + item.pl_length[num][6] + item.pl_length[num][7]);

        for (i = 1; i < size; i++)
        {
            printf(" ");
        }
        printf("|");

        printf("\n|                   %s", t_player[num][8].player_name);
        for (i = 9; i <= 10; i++)
        {
            printf(", %s", t_player[num][i].player_name);
        }
        size = 97 - (24 + item.pl_length[num][8] + item.pl_length[num][9] + item.pl_length[num][10]);

        for (i = 1; i < size; i++)
        {
            printf(" ");
        }
        printf("|\n");

        num++;
    }
    printf("|_______________________________________________________________________________________________|\n");
}
int main()
{
    char opener,N_striker, same[2], team[2][35], venue[30], opt, umpire[30], date[15], m_time[10], w_toss[25], l_toss[25], batting_team[35], fielding_team[35],st_runs_scored[4],st_ball_faced[4],nst_runs_scored[4],nst_ball_faced[4],total_runs[2][4],total_wkts[2][4],s_this_over[4],wicket_str[11][100]={},wk[20];
    int number,k[1], i,st[2],n_st[2],pl1=0,pl2=1, overs,loop, count = 1, a,bowler_no,byes[2], leg_byes[2], batting, fielding, wicket=0,total=0,pos=0,l_pscore[5],l_ballf[5],l_total[2],l_wicket[2],l_this_over,size;
    pl t_player[2][11], b_o[2][11];
    l item;
    ex extra[2]={};    
    bl bowlers[2][11]={};
    bt batsmen[2][11]={};
    wckts w_team[2][11]={};
    pos=0;


    printf("\n\t\t\t\t\t\t\e[37;4m\e[1mMATCH BETWEEN\n");
    printf("\e[36mFIRST TEAM\e[0m : ");
    gets(team[0]);
    fflush(stdin);
    for (a = 0; a < 2; a++)
    {
        printf("\n\e[33;1mCaptain\e[0m : ");
        gets(t_player[a][0].player_name);
        //  printf("Role : ");
        // gets(t_player[a][0].role);
        printf("\e[33;1mWicket-Keeper\e[0m : ");
        gets(t_player[a][1].player_name);
        strcpy(wk,t_player[a][1].player_name);
        // printf("Role : ");
        // gets(t_player[a][1].role);
        printf("Opener(Striker) : ");
        gets(t_player[a][2].player_name);
        printf("Opener(Non-Striker) : ");
        gets(t_player[a][3].player_name);

        if (strcmp(t_player[a][0].player_name, t_player[a][1].player_name) == 0)
        {
            same[a] = 's';

            if (strcmp(t_player[a][0].player_name, t_player[a][2].player_name) == 0)
            {
                opener = 'c';
                strcpy(b_o[a][0].player_name, (t_player[a][2].player_name));
                strcpy(b_o[a][1].player_name, (t_player[a][3].player_name));
                strcpy(t_player[a][1].player_name, (t_player[a][3].player_name));
                i = 2;
            }
            else if (strcmp(t_player[a][0].player_name, t_player[a][3].player_name) == 0)
            {
                N_striker = 'c';
                strcpy(b_o[a][1].player_name, (t_player[a][0].player_name));
                strcpy(b_o[a][0].player_name, (t_player[a][2].player_name));
                strcpy(t_player[a][1].player_name, (t_player[a][2].player_name));
                i = 2;
            }
            else
            {
                strcpy(b_o[a][0].player_name, (t_player[a][2].player_name));
                strcpy(b_o[a][1].player_name, (t_player[a][3].player_name));
                strcpy(b_o[a][2].player_name, (t_player[a][0].player_name));
                strcpy(t_player[a][1].player_name, (t_player[a][2].player_name));
                strcpy(t_player[a][2].player_name, (t_player[a][3].player_name));
                i = 3;
            }
        }

        else if (strcmp(t_player[a][0].player_name, t_player[a][2].player_name) == 0)
        {
            opener = 'c';
            strcpy(b_o[a][0].player_name, (t_player[a][2].player_name));
            if (strcmp(t_player[a][1].player_name, t_player[a][3].player_name) == 0)
            {
                strcpy(b_o[a][1].player_name, (t_player[a][3].player_name));
                i = 2;
            }
            else
            {
                strcpy(t_player[a][2].player_name, (t_player[a][3].player_name));
                strcpy(b_o[a][1].player_name, (t_player[a][3].player_name));
                strcpy(b_o[a][2].player_name, (t_player[a][1].player_name));

                i = 3;
            }
        }
        else if ((strcmp(t_player[a][0].player_name, t_player[a][3].player_name) == 0))
        {
            strcpy(b_o[a][1].player_name, (t_player[a][0].player_name));

            if (strcmp(t_player[a][1].player_name, t_player[a][2].player_name) == 0)
            {
                opener = 'w';
                strcpy(b_o[a][0].player_name, (t_player[a][1].player_name));

                i = 2;
            }
            else
            {              
                strcpy(b_o[a][0].player_name, (t_player[a][2].player_name));
                strcpy(b_o[a][2].player_name, (t_player[a][1].player_name));
                i = 3;
            }
        }
        else if ((strcmp(t_player[a][1].player_name, t_player[a][2].player_name) == 0))
        {
            strcpy(b_o[a][0].player_name, (t_player[a][2].player_name));
            opener = 'w';
            if (strcmp(t_player[a][0].player_name, t_player[a][3].player_name) == 0)
            {
                strcpy(b_o[a][1].player_name, (t_player[a][3].player_name));
                N_striker = 'c';

                i = 2;
            }
            else
            {
                strcpy(b_o[a][2].player_name, (t_player[a][0].player_name));
                strcpy(b_o[a][1].player_name, (t_player[a][3].player_name));
                strcpy(t_player[a][2].player_name, (t_player[a][3].player_name));

                i = 3;
            }
        }
        else if ((strcmp(t_player[a][1].player_name, t_player[a][3].player_name) == 0))
        {
            N_striker = 'c';
            strcpy(b_o[a][1].player_name, (t_player[a][3].player_name));

            if (strcmp(t_player[a][0].player_name, t_player[a][2].player_name) == 0)
            {
                opener = 'w';
                strcpy(b_o[a][0].player_name, (t_player[a][2].player_name));

                i = 2;
            }
            else
            {
                strcpy(t_player[a][2].player_name, (t_player[a][0].player_name));
                strcpy(b_o[a][2].player_name, (t_player[a][0].player_name));
                strcpy(b_o[a][0].player_name, (t_player[a][2].player_name));

                i = 3;
            }
        }
        else
        {
            strcpy(b_o[a][0].player_name, (t_player[a][2].player_name));
            strcpy(b_o[a][1].player_name, (t_player[a][3].player_name));
            strcpy(b_o[a][2].player_name, (t_player[a][0].player_name));
            strcpy(b_o[a][3].player_name, (t_player[a][1].player_name));

            i = 4;
        }

        for (i; i < 11; i++)
        {
            printf("Player %d : ", i + 1);
            gets(t_player[a][i].player_name);
            fflush(stdin);
            strcpy(b_o[a][i].player_name, t_player[a][i].player_name);
            //    printf("Role : ");
            // gets(t_player[a][i].role);
        }
        if (count == 2)
        {   break;
        }
        count++;
        printf("\n\n\e[36;4m\e[1mSECOND TEAM\e[0m : ");
        gets(team[1]);
        fflush(stdin);
    }
    printf("\n\n\e[36;1mOvers\e[0m : ");
    scanf("%d", &overs);
    fflush(stdin);
    int this_over[overs];
    printf("\e[36;1mVenue\e[0m : ");
    gets(venue);
    fflush(stdin);
    printf("\e[36;1mDate\e[0m : ");
    gets(date);
    printf("\e[36;1mTime\e[0m : ");
    gets(m_time);
    printf("\e[36;1mUmpire Name\e[0m : ");
    gets(umpire);
    fflush(stdin);

    srand((time(0)));
    number = rand() % 2;
    printf("\nHere we go!!!\nTossing the coin");
    for(i=0;i<4;i++)
    {   Sleep(500);
        printf(".");
    }Sleep(500);
    if (number == 0)
    {
        strcpy(w_toss, team[0]);
        strcpy(l_toss, team[1]);

        printf("\n\n\e[37;4m\e[1m%s\e[0m has won the toss.", w_toss);
    }
    else
    {
        strcpy(w_toss, team[1]);
        strcpy(l_toss, team[0]);
        printf("\n\n\e[1m\e[4m%s\e[0m has won the toss.", w_toss);
    }
    Sleep(1000);

    printf("\nWhat you gonna choose B/F for BAT/FIELD : ");
    scanf("%c", &opt);
    fflush(stdin);
    Sleep(1000);

    item.team_l[0] = strlen(team[0]);
    item.team_l[1] = strlen(team[1]);
    item.date_l = strlen(date);
    // item.overs_l = strlen(overs);
    item.m_time_l = strlen(m_time);
    item.umpire_l = strlen(umpire);
    item.venue_l = strlen(venue);
    item.w_toss_l = strlen(w_toss);
    item.l_toss_l = strlen(l_toss);
    for ( i = 0; i < 11; i++)
    {
        item.pl_length[0][i] = strlen(b_o[0][i].player_name);
        item.pl_length[1][i] = strlen(b_o[1][i].player_name);
    }

   matchinfo(date, m_time, venue, opt, umpire, team, t_player, b_o, overs, w_toss, l_toss, item, same);
    Sleep(1000);
    if (opt == 'b' || opt == 'B')
    {
        printf("\n%s is Batting first\n", w_toss);
    }
    else
    {
        printf("\n%s is Batting first\n", l_toss);
    }

    printf("\nThe countdown begins..3..2..1..\n\n\t\t\tPLAY\n");
    Sleep(2000);
    printf(" __________________________________________________________ \n");
    printf("|                     SHORTCUT KEYS                        |\n");
    printf("|__________________________________________________________|\n");
    printf("|   WORDS                           CHARACTERS TO BE USED  |\n");
    printf("|                                                          |\n");
    printf("| 1) NO BALL               -               'N' / 'n'       |\n");
    printf("| 2) WIDE BALL             -               'D' / 'd'       |\n");
    printf("| 3) WICKET                -               'W' / 'w'       |\n");
    printf("| 4) BYE RUNS              -               'B' / 'b'       |\n");
    printf("| 5) LEG_BYE RUNS          -               'L' / 'l'       |\n");
    printf("|__________________________________________________________|\n");
    count = 0;
    int j ;
   
   
    if (strcmp(w_toss, team[0]) == 0 && (opt == 'b' || opt == 'B'))
    {
        strcpy(batting_team, team[0]);
        strcpy(fielding_team, team[1]);
        batting = 0;
        fielding = 1;
    }
    else if (strcmp(w_toss, team[0]) == 0 && (opt == 'f' || opt == 'F'))
    {
        strcpy(fielding_team, team[0]);
        strcpy(batting_team, team[1]);
        batting = 1;
        fielding = 0;
    }
    else if (strcmp(w_toss, team[1]) == 0 && (opt == 'f' || opt == 'F'))
    {
        strcpy(batting_team, team[0]);
        strcpy(fielding_team, team[1]);
        batting = 0;
        fielding = 1;
    }

    else if (strcmp(w_toss, team[1]) == 0 && (opt == 'b' || opt == 'B'))
    {
        strcpy(fielding_team, team[0]);
        strcpy(batting_team, team[1]);
        batting = 1;
        fielding = 0;
    }
   

    batsmen[batting][0].out=1;
    batsmen[batting][0].count=1;
    batsmen[batting][1].count=0;
    batsmen[batting][1].out=1;
    st[batting]=0;
    pos=st[batting];
    n_st[batting]=1;
    char runs[2][overs][6];
    char* runs_po[2][overs][13];
    int over_extra[overs];
    
    
 
    for (i = 0; i < overs; i++)
    {
        over_extra[i]=0;
        

        // runs_po[2][i][10]={};
        printf("\n\nEnter player no. from the team %s to bowl over no. %d : ",fielding_team, i+1);
        scanf("%d", &bowler_no);
        fflush(stdin);
        bowlers[fielding][bowler_no-1].overs++;
        if(count>0)
        printf("\n%s, comes into the attack to bowl the next over.\n",b_o[fielding][bowler_no-1].player_name);

        
        if(count==0)
        {
            printf("\n\e[33;4m%s\e[0m and \e[33;4m%s\e[0m are at the crease.", b_o[batting][0].player_name, b_o[batting][1].player_name);
            printf("\n\e[33;4m%s\e[0m is on the strike. \e[32;4m%s\e[0m will open the attack.\n", b_o[batting][0].player_name, b_o[fielding][bowler_no - 1].player_name);
            count++;
        }
        this_over[i]=0;
        k[0]=0;
        for (j = 1; j < 7; j++)
        { 
                
            runs_checker(i, j,st,n_st,&pl1,&pl2,&pos, &total,extra, b_o, batting,&wicket, wk,fielding, bowler_no, batsmen, bowlers,this_over,overs,runs,runs_po,wicket_str,t_player,over_extra,k);
        }
            if(*runs_po[batting][i][k[0]]=='0' || *runs_po[batting][i][k[0]]=='2' || *runs_po[batting][i][k[0]]=='4' || *runs_po[batting][i][k[0]]=='6' || *runs_po[batting][i][k[0]]=='w' || *runs_po[batting][i][k[0]]=='W'  )
            {
                if (batsmen[batting][0].count==1  && (pos==st[batting]))
                {
                        batsmen[batting][0].count=0;
                        pos=n_st[batting];
                }
                else if (batsmen[batting][0].count==0 && (pos==n_st[batting]))
                {
                    batsmen[batting][0].count=1;
                    pos=st[batting];
                     }          
            }
            else if(*runs_po[batting][i][k[0]]=='1' || *runs_po[batting][i][k[0]]=='3')
            {
                if (batsmen[batting][0].count==1  && (pos==st[batting]))
                {
                        batsmen[batting][0].count=0;
                        pos=n_st[batting];
                        }
                else if (batsmen[batting][0].count==0 && (pos==n_st[batting]))
                {
                    batsmen[batting][0].count=1;
                    pos=st[batting];     
                   }
            }
            //printf("%d",k[0]);
            int loop=k[0]+1;
            for(loop;loop<=13; loop++)
        {
             runs_po[batting][i][loop]=NULL;
             
        }
       // runs_po[batting][i][loop]=NULL;}
        item.team_l[0] = strlen(team[batting]);
        if( item.team_l[0]<=15)
        printf("\n\e[33;1m ______________________________________________________________________________________________________________________\e[0m \n");
        else
        printf("\n\e[33;1m ______________________________________________________________________________________________________________________________ \e[0m\n");
                printf("\n");
                 if(i<9)
                {
                printf("   0%d    Runs Scored: ",i+1);}
                else
                {printf("   %d    Runs Scored: ",i+1);}
                if(this_over[i]<10)
                printf("0%d",this_over[i]);
                
                else
                printf("%d",this_over[i]);
                

                printf("        Score after ");
                if(i<9)
                {
                    printf("0%d",i+1);
                }
                else
                printf("%d",i+1);

                if(item.team_l[0]<=15)
                { if(i!=0)
                  printf(" overs     ");
                  else
                  printf(" over      ");}
                else
                {if(i!=0)
                  printf(" overs             ");
                  else
                  printf(" over              ");}

               
                sprintf(st_runs_scored, "%.f", batsmen[batting][st[batting]].runs_scored);
                sprintf(st_ball_faced, "%d", batsmen[batting][st[batting]].ball_faced);

                sprintf(nst_runs_scored, "%.f", batsmen[batting][n_st[batting]].runs_scored);
                sprintf(nst_ball_faced, "%d", batsmen[batting][n_st[batting]].ball_faced);
                l_pscore[0]=strlen(st_runs_scored);
                l_ballf[0]=strlen(st_ball_faced);
                l_ballf[1]=strlen(nst_ball_faced);
                l_pscore[1]=strlen(nst_runs_scored);
               // printf("\nst %.f runs length : %d\n",batsmen[batting][st[batting]].runs_scored,l_pscore[0]);
                printf("%s",b_o[batting][st[batting]].player_name);
                j=28-(item.pl_length[batting][st[batting]]+8);
                for(loop=1;loop<=j;loop++)
                printf(" ");
                j=8-(l_pscore[0]+l_ballf[0]+2);
                for(loop=1;loop<=(j);loop++)
                printf(" ");
                printf("%.f(%d)     ",batsmen[batting][st[batting]].runs_scored,batsmen[batting][st[batting]].ball_faced);
                printf("%s",b_o[fielding][bowler_no-1].player_name);
                j=23-(item.pl_length[fielding][bowler_no-1]+5);
                for(loop=1;loop<=j;loop++)
                printf(" ");
                printf("Extras : %d",over_extra[i]);
                           
               if(k[0]==6)
                printf("\n         %c %c %c %c %c %c %c %c %c    ",*runs_po[batting][i][1],*runs_po[batting][i][2],*runs_po[batting][i][3],*runs_po[batting][i][4],*runs_po[batting][i][5],*runs_po[batting][i][6],runs_po[batting][i][7],runs_po[batting][i][8],runs_po[batting][i][9],runs_po[batting][i][10],runs_po[batting][i][11],runs_po[batting][i][12]);
                else if(k[0]==7)
               printf("\n         %c %c %c %c %c %c %c %c %c   ",*runs_po[batting][i][1],*runs_po[batting][i][2],*runs_po[batting][i][3],*runs_po[batting][i][4],*runs_po[batting][i][5],*runs_po[batting][i][6],*runs_po[batting][i][7],runs_po[batting][i][8],runs_po[batting][i][9],runs_po[batting][i][10],runs_po[batting][i][11],runs_po[batting][i][12]);
               else if(k[0]==8)
                printf("\n         %c %c %c %c %c %c %c %c %c  ",*runs_po[batting][i][1],*runs_po[batting][i][2],*runs_po[batting][i][3],*runs_po[batting][i][4],*runs_po[batting][i][5],*runs_po[batting][i][6],*runs_po[batting][i][7],*runs_po[batting][i][8],runs_po[batting][i][9],runs_po[batting][i][10],runs_po[batting][i][11],runs_po[batting][i][12]);
                else if(k[0]==9)
                printf("\n         %c %c %c %c %c %c %c %c %c ",*runs_po[batting][i][1],*runs_po[batting][i][2],*runs_po[batting][i][3],*runs_po[batting][i][4],*runs_po[batting][i][5],*runs_po[batting][i][6],*runs_po[batting][i][7],*runs_po[batting][i][8],*runs_po[batting][i][9],runs_po[batting][i][10],runs_po[batting][i][11],runs_po[batting][i][12]);
                else if(k[0]==10)
                printf("\n         %c %c %c %c %c %c %c %c %c ",*runs_po[batting][i][1],*runs_po[batting][i][2],*runs_po[batting][i][3],*runs_po[batting][i][4],*runs_po[batting][i][5],*runs_po[batting][i][6],*runs_po[batting][i][7],*runs_po[batting][i][8],*runs_po[batting][i][9],*runs_po[batting][i][10],runs_po[batting][i][11],runs_po[batting][i][12]);
                 else if(k[0]==11)
                printf("\n         %c %c %c %c %c %c %c %c %c ",*runs_po[batting][i][1],*runs_po[batting][i][2],*runs_po[batting][i][3],*runs_po[batting][i][4],*runs_po[batting][i][5],*runs_po[batting][i][6],*runs_po[batting][i][7],*runs_po[batting][i][8],*runs_po[batting][i][9],*runs_po[batting][i][10],*runs_po[batting][i][11],runs_po[batting][i][12]);
                  else if(k[0]==12)
                printf("\n         %c %c %c %c %c %c %c %c %c ",*runs_po[batting][i][1],*runs_po[batting][i][2],*runs_po[batting][i][3],*runs_po[batting][i][4],*runs_po[batting][i][5],*runs_po[batting][i][6],*runs_po[batting][i][7],*runs_po[batting][i][8],*runs_po[batting][i][9],*runs_po[batting][i][10],*runs_po[batting][i][11],*runs_po[batting][i][12]);
                 size=23-18;
                for(loop=0;loop<size;loop++)
                printf(" ");

                 printf("%s %d-%d",batting_team,total,wicket);
                              
                
                 sprintf(total_runs[0], "%d", total);
                 sprintf(total_wkts[0], "%d", wicket);
                l_total[batting]=strlen(total_runs[batting]);
                l_wicket[batting]=strlen(total_wkts[batting]);

                 if(item.team_l[0]<=15)
                {size=25-(item.team_l[batting]+l_total[batting]+l_wicket[batting]+2);}
                else
                {size=33-(item.team_l[batting]+l_total[batting]+l_wicket[batting]+2);}
                
                for(loop=1;loop<=size;loop++)
                printf(" ");
                printf("%s",b_o[batting][n_st[batting]].player_name);
                j=28-(item.pl_length[batting][n_st[batting]]+8);
                for(loop=1;loop<=j;loop++)
                printf(" ");
                j=8-(l_pscore[1]+l_ballf[1]+2);
                for(loop=1;loop<=(j);loop++)
                printf(" ");
                printf("%.f(%d)     ",batsmen[batting][n_st[batting]].runs_scored,batsmen[batting][n_st[batting]].ball_faced);
               printf("%d-%d-%d-%d",bowlers[fielding][bowler_no-1].overs,bowlers[fielding][bowler_no-1].maiden,bowlers[fielding][bowler_no-1].runs_conceded,bowlers[fielding][bowler_no-1].wickets);
               //printf("\n l_pscore[1] - %d    l_ballf[1] - %d",l_pscore[1],l_ballf[1]);
                  if( item.team_l[0]<=15)
        printf("\n \e[33;1m______________________________________________________________________________________________________________________ \e[0m\n");
        else
        printf("\n\e[33;1m ______________________________________________________________________________________________________________________________ \e[0m\n");
              
    }
    char not_out[12]={"not out"};
     if(batsmen[batting][n_st[batting]].out==1 )
     strcpy(wicket_str[n_st[batting]],not_out);
     if(batsmen[batting][st[batting]].out==1 )
     strcpy(wicket_str[st[batting]],not_out); 
    printf("\n\n\n");
   
    
    printf("\n\n\n");
Sleep(1000);
//printf("\t\t\t\t\tScorecard");
printf("\n ____________________________________________________________________________________________________________ \n");
printf("|                                                                                                            |\n");
printf("| %s Innings",batting_team);
size=110-(25+item.team_l[batting]);
for(j=1;j<size;j++)
printf(" ");
if(l_total[batting]==1)
printf("  %d",total);
else if(l_total[batting]==2)
printf(" %d",total);
else 
printf("%d",total);
if(wicket<10)
printf("/%d ",wicket);
else
printf("/%d",wicket);
if(overs<10)
printf(" (0%d Ov) |\n",overs);
else if(overs>=10)
printf(" (%d Ov) |\n",overs);
printf("|____________________________________________________________________________________________________________|\n");
printf("| Batter                                                                R      B      4s     6s     SR       |\n");
printf("|____________________________________________________________________________________________________________|\n");
for(i=0;i<11;i++)
{
item.wicket_str_l[batting][i]=strlen(wicket_str[i]);
printf("| %s",b_o[batting][i].player_name);
size=25-(item.pl_length[batting][i]);
for(j=1;j<size;j++)
printf(" "); 
printf("     %s",wicket_str[i]);    
size=70 - (30+ item.wicket_str_l[batting][i]);
for(j=1;j<size;j++)
printf(" ");
if(batsmen[batting][i].runs_scored>=0 && batsmen[batting][i].runs_scored<10)
printf("  %.f  ",batsmen[batting][i].runs_scored);
else if(batsmen[batting][i].runs_scored>=10 && batsmen[batting][i].runs_scored<100)
printf(" %.f  ",batsmen[batting][i].runs_scored);
else
printf("%.f  ",batsmen[batting][i].runs_scored);
if(batsmen[batting][i].ball_faced>=0 && batsmen[batting][i].ball_faced<10)
printf("    %d  ",batsmen[batting][i].ball_faced);
else if(batsmen[batting][i].ball_faced>=10 && batsmen[batting][i].ball_faced<100)
printf("   %d  ",batsmen[batting][i].ball_faced);
else
printf("  %d  ",batsmen[batting][i].ball_faced);
if(batsmen[batting][i].fours>=0 && batsmen[batting][i].fours<10)
printf("     %d   ",batsmen[batting][i].fours);
else 
printf("    %d   ",batsmen[batting][i].fours);
if(batsmen[batting][i].sixes>=0 && batsmen[batting][i].sixes<10)
printf("   %d   ",batsmen[batting][i].sixes);
else 
printf("  %d   ",batsmen[batting][i].sixes);
if(batsmen[batting][i].strike_rate==0)
printf("  0.00     |\n");
else
printf("  %.2f   |\n",batsmen[batting][i].strike_rate);
}
printf("|____________________________________________________________________________________________________________|\n");

   // printf("%s - %d/%d (%d)",batting_team,total,wicket,overs);
    printf("Extras: %d      b-%d,lb-%d,wd-%d,n-%d\n\n",extra[batting].b+extra[batting].lb+extra[batting].wd+extra[batting].n,extra[batting].b,extra[batting].lb,extra[batting].wd,extra[batting].n); 
    return 0;
}