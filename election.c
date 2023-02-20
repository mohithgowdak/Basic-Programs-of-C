#include <stdio.h>
#include<string.h>
typedef struct Voters
{
  char name[49];
  long long voterid;
  int vote;
} Voter;
int authenticateAdmin ();
int get_int_len (long long);
int voting ();
int result ();
int Adminpanel ();
void enterdetails ();
void voterlist ();
void delete (long long int *p, int pos, int j);
int max_voters;
int o = 50;
typedef struct candidates
{
  char name1[10];
} CAN;
int
main ()
{
  while (1)
    {
      printf ("\n\t\t\t 1. to vote \n\t\t\t 2.ADMIN PANEL \n\t\t\t 3.Exit \n\t\t\t Option:");
      char input;
      scanf (" %c", &input);
      switch (input)
	{
	case '1':
	  voting ();
	  break;
	case '2':
	  Adminpanel ();
	  break;
	case '3':
	  return 0;
	default:
	  printf ("\nInvalid option");
	}
    }
  return 0;
}

int
get_int_len (long long value)
{
  int l = 1;
  while (value > 9)
    {
      l++;
      value /= 10;
    }
  return l;
}

int
result ()
{
  int a = 0;
  int b = 0;
  FILE *file = fopen ("VotingData.txt", "r");
  Voter voter[100];
  int read = 0;
  int records = 0;
  if (file == NULL)
    {
      printf ("Error opening file\n");
      return 1;
    }
  do
    {
      read = fscanf (file, "%49[^,],%lld,%d",
		     voter[records].name,
		     &voter[records].voterid, &voter[records].vote);
      if (read == 3)
	records++;
      if ((read != 3) && !feof (file))
	{
	  printf ("File formar error on index[%d]\n", records);
	  continue;
	}
      if (ferror (file))
	{
	  printf ("Error reading file.\n");
	  return 1;
	}
    }
  while (!feof (file));
  fclose (file);
  printf ("\n\n%d votes read\n\n", records);
  for (int i = 0; i < records; i++)
    {
      if (get_int_len (voter[i].voterid) != 12)
	{
	  printf ("Voter ID [%lld] is not valid (vote invalid)\n",
		  voter[i].voterid);
	  continue;
	}
      else
	{
	  switch (voter[i].vote)
	    {
	    case 1:
	      a++;
	      break;
	    case 2:
	      b++;
	      break;
	    default:
	      break;
	    }
	}
    }
  FILE *file1 = fopen ("candidate.txt", "r");
  CAN z[2];
  int i = 0;
  do
    {
      int read1 = fscanf (file1, "%s", z[i].name1);
      i++;
    }
  while (!feof (file1));
  fclose (file1);
  printf ("%s:%d and %s:%d\n", z[0].name1, a, z[1].name1, b);
  if (a == b)
    printf ("TIE!!");
  else if (a > b)
    printf ("%s", z[0].name1);
  else
    printf ("%s", z[1].name1);
  if (a != b)
    {
      printf ("with %.2f%% votes",
	      (((a > b) ? a : b) / (float) records) * 100);
    }
  return 0;
}

int
authenticateAdmin ()
{
  char username[15], password[6], x;
  printf ("\nEnter username: ");
  scanf ("%s", username);
  if ((strcmp (username, "Admin")) != 0)
    return 0;
  else
    {
      printf ("Enter Password: ");
      scanf ("%s", password);
      if ((strcmp (password, "0707")) != 0)
	return 0;
    }
  return 1;
}

int
voting ()
{
  FILE *file1 = fopen ("candidate.txt", "r");
  CAN z[2];
  int i = 0;
  do
    {
      printf ("0000");
      int read1 = fscanf (file1, "%s", z[i].name1);
      i++;
    }
  while (!feof (file1));
  fclose (file1);
  FILE *file3 = fopen ("voterlist.txt", "r");
  long long int a[100];
  int j = 0;
  for (j = 0; !feof (file1); j++)
    {
      int read3 = fscanf (file3, "%lld", &a[j]);
    } j++;
  fclose (file3);
  FILE *file = fopen ("VotingData.txt", "a");
  if (file == NULL)
    {
      printf ("Error opening file.\n");
      return 1;
    }
  printf ("\t\t\tWelcome to MiniVote, a voting system between two people.\n");
  printf ("enter the number of voters at this session\n");
  scanf ("%d", &max_voters);
  Voter voters[max_voters];
  // taking input
  int attendees = 0;
  char cont = 'Y';
  while (attendees < max_voters && (cont == 'Y' || cont == 'y'))
    {
    L3:
      printf ("enter 1 to vote candidate %s\n enter 2 to vote candidate %s\n", z[0].name1, z[1].name1);
      printf ("\nVoter No: %d\n", attendees + 1);
      printf ("__________\n");
      printf ("Enter your name : ");
      scanf (" %[^\n]s", voters[attendees].name);
      printf ("Enter your 12 digit Voter ID : ");
      scanf ("%lld", &voters[attendees].voterid);
      int x = 0;
      int flag = 0;
      for (int i = 0; i < o; i++)
	{
	  if (a[i] == voters[attendees].voterid)
	    {
	      x = i;
	      flag = 1;
	      break;
	    }
	}
      if (flag == 0)
	{
	  printf ("the voter is not elegible to VOTE\n");
	  goto L3;
	}
      delete (a, x, j);
      printf ("Enter your Vote : ");
      scanf ("%d", &voters[attendees].vote);
      printf ("__________\n");
      attendees++;
      if (attendees < max_voters)
	{
	  printf ("\nDo you want to continue? [Y/N]\n");
	  scanf (" %c", &cont);
	}
      else
	{
	  printf ("\nElection completed.\n");
	}
    }
  FILE *file4 = fopen ("voterlist.txt", "w");
  for (int i = 0; i < o; i++)
    {
      fprintf (file4, "%lld\n", a[i]);
    }
  fclose (file4);
  for (int i = 0; i < attendees; i++)
    {
      fprintf (file, "%s, %lld, %d\n", voters[i].name, voters[i].voterid,
	       voters[i].vote);
    }
  fclose (file);
  if (attendees > 1)
    {
      printf ("%d people voted.\n", attendees);
    }
  else
    {
      printf (((attendees ==
		0) ? ("No one voted.\n") : ("1 person voted.\n")));
    }
  return 0;
}

int
Adminpanel ()
{
  char a[10], b[10];
L1:
  if (authenticateAdmin () != 1)
    {
      printf ("\n Wrong Username or Password \n");
      goto L1;
    }
  printf ("\n\nLOGGED IN SUCCESSFULLY (Press Enter)");
  while (1)
    {
      printf
	("\n\t\t\t 1. enter candidate\n\t\t\t 2.to check results \n\t\t\t 3.to voters list\n\t\t\t 4.Exit \n\t\t\t Option:");
      char input;
      scanf (" %c", &input);
      switch (input)
	{
	case '1':
	  enterdetails ();
	  break;
	case '2':
	  result ();
	  break;
	case '3':
	  voterlist ();
	  break;
	case '4':
	  return 0;
	default:
	  printf ("\nInvalid option");
	}
    }
}

void
enterdetails ()
{
  CAN z[2];
  printf ("enter the name of candidate 1");
  scanf ("%s", z[0].name1);
  printf ("enter the name of candidate 2");
  scanf ("%s", z[1].name1);
  FILE *file1 = fopen ("candidate.txt", "a");
  for (int i = 0; i < 2; i++)
    {
      fprintf (file1, "%s\n", z[i].name1);
    }
  fclose (file1);
}

void
voterlist ()
{
  long long int a[100];
  long long int z;
  z = 123456789101;
  for (int i = 0; i < o; i++)
    {
      a[i] = z;
      z = z + 1;
    }
  FILE *file2 = fopen ("voterlist.txt", "a");
  for (int i = 0; i < o; i++)
    {
      fprintf (file2, "%lld\n", a[i]);
    }
  fclose (file2);
}

void
delete (long long int *p, int pos, int j)
{
  int i;
  printf ("YOU CANNOT VOTE AGAIN\n");
  for (i = pos; i < j; i++)
    {
      *(p + i) = *(p + i + 1);
    }
  o--;
}
