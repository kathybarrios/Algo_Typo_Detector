#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <fstream>

using namespace std;
#define MATCH       0 	/* macro match	*/
#define INSERT      1 	/* macro insert 	*/
#define DELETE      2 	/* macro delete 	*/
#define SUB			3 	/* macro sub 		*/
#define TRANS       4 	/* macro trans 	*/
#define MAXLEN 50		/* Modify to fit sentence cases */

typedef struct {
    int cost;     		/* cost of reaching this cell */
    int parent;   		/* parent cell */
} cell;

cell m[MAXLEN+1][MAXLEN+1];

/*int keyDist (char *char1, char *char2)
{
    int rowDist = abs(getKeyLocation(*char2).row - getKeyLocation(*char1).row);
    int colDist = abs(getKeyLocation(*char2).col - getKeyLocation(*char1).col);

    if (rowDist > colDist)
        return rowDist;
    return colDist;
}

buttons getKeyLocation(char key) {
    return keys[row][col];
}*/

ofstream myfile("output.txt");

/*********** reconstruction ***********/
void match_out(char &s, char &t, int &i, int &j) 
{

}
void insert_out(char t, int &j) 
{
    myfile << "Insert " << t << " before " << j << endl;
}
void delete_out(char &s, int &i) 
{
    myfile << "Delete " << i << endl;
}
void sub_out(char s, int &i) 
{
    myfile << "Substitute " << s << " at " << i << endl;
}
void trans_out(char &s, char &t, int &i, int &j) 
{
    myfile << "Transpose " << i-1 << " - " << i << endl;
}

/*void reconstruct_path(char *s, char *t, int i, int j) 
{
    if (m[i][j].parent == -1) return;
    if (m[i][j].parent == MATCH) 
    {
        reconstruct_path(s,t,i-1,j-1);
        match_out(s, t, i, j);
        return;
    }
    if (m[i][j].parent == INSERT) 
    {
        reconstruct_path(s,t,i,j-1);
        insert_out(t,j);
        return;
    }
    if (m[i][j].parent == DELETE) 
    {
        reconstruct_path(s,t,i-1,j);
        delete_out(s,i);
        return;
    }
    if (m[i][j].parent == SUB) 
    {
        reconstruct_path(s,t,i,j);
        sub_out(s,i);
        return;
    }
    if (m[i][j].parent == TRANS) 
    {
        reconstruct_path(s,t,i-2,j-2);
        trans_out(s,t,i,j);
        return;
    }
}*/

/*********** initializations ***********/
void row_init (int i) 
{
    m[0][i].cost = i;
    if (i>0)
        m[0][i].parent =  INSERT;
    else
        m[0][i].parent = -1;
}

void column_init (int i) 
{
    m[i][0].cost = i;
    if (i>0)
        m[i][0].parent = DELETE;
    else
        m[i][0].parent = -1;
}

/*********** edit distance ***********/
void goal_cell(char *s, char *t, int *i, int *j) 
{
    *i = strlen(s) - 1;
    *j = strlen(t) - 1;
}

int match ( char s, char t ) 
{
    if ( s==t )
        return 0;
    else
        return 1;
}

int insert ( char *s, char *t, int *i, int *j )
{
    if ( !( (*i < MAXLEN) && (*j < MAXLEN) ))
    {
        return 10;
    }
    
    if((*i == *j) && (s[*i] != t[*j]) && (s[*i+1] != t[*j+1]) && (s[*i] != t[*j-1]) && (t[*j] != s[*i+1]))
    {
        //Inserting Repeated Character
        if((s[*i-1] == t[*j-1]) && (t[*j-1] == t[*j]) && (s[*i] != t[*j])) 
        {
            insert_out(t[*j],*j);
            for(int a = strlen(s)-1; a >= *i; a--)
            {
                s[a+1] = s[a];
            }
            s[*i] = t[*j];
            return 1;
        }
        //Inserting Space after key on bottom row
        else if ((s[*i-1] == t[*j-1]) && (t[*j] == ' ') && (s[*i] != t[*j])) 
        {
            if(s[*i-1] == 'z' || s[*i-1] == 'x' || s[*i-1] == 'c' || s[*i-1] == 'v' || s[*i-1] == 'b' || s[*i-1] == 'n' || s[*i-1] == 'm' || s[*i-1] == ',' || s[*i-1] == '.')
            {
                insert_out(t[*j],*j);
                for(int a = strlen(s); a >= *i; a--)
                {
                    s[a+1] = s[a];
                }
                s[*i] = t[*j];
                return 2;
            }
            //Inserting Space after something else
            else 
            {
                insert_out(t[*j],*j);
                for(int a = strlen(s); a >= *i; a--)
                {
                    s[a+1] = s[a];
                }
                s[*i] = t[*j];
                return 6;
            }
        }
        //Inserting character before a space
        else if((s[*i-1] == t[*j-1]) && (s[*i] == ' ') && (t[*j] != ' ') && (s[*i+1] != t[*j])) 
        {
            insert_out(t[*j],*j);
            for(int a = strlen(s); a >= *i; a--)
            {
                s[a+1] = s[a];
            }
            s[*i] = t[*j];
            return 6;
        }
        //Inserting after another key on same hand -- left to left
        else if(((s[*i-1] == t[*j-1]) && (s[*i] != t[*j]) && (s[*i] == t[*j+1])) && (s[*i] == '1' || s[*i] == '2'  || s[*i] == '3' || s[*i] == '3' || s[*i] == '4' || s[*i] == '5' || s[*i] == 'q' || s[*i] == 'w' || s[*i] == 'e' || s[*i] == 'r' || s[*i] == 't' || s[*i] == 'a' || s[*i] == 's' || s[*i] == 'd' || s[*i] == 'f' || s[*i] == 'g' || s[*i] == 'z' || s[*i] == 'x' || s[*i] == 'c' || s[*i] == 'v' || s[*i] == 'b') && (t[*j] == '1' || t[*j] == '2'  || t[*j] == '3' || t[*j] == '3' || t[*j] == '4' || t[*j] == '5' || t[*j] == 'q' || t[*j] == 'w' || t[*j] == 'e' || t[*j] == 'r' || t[*j] == 't' || t[*j] == 'a' || t[*j] == 's' || t[*j] == 'd' || t[*j] == 'f' || t[*j] == 'g' || t[*j] == 'z' || t[*j] == 'x' || t[*j] == 'c' || t[*j] == 'v' || t[*j] == 'b')) //left hand
        {
            insert_out(t[*j],*j);
            for(int a = strlen(s); a >= *i; a--)
            {
                s[a+1] = s[a];
            }
            s[*i] = t[*j];
                //d(k1,k2); TODO
        }
        //Inserting after another key on same hand -- right to right
        else if(((s[*i-1] == t[*j-1]) && (s[*i] != t[*j]) && (s[*i] == t[*j+1])) && (s[*i] == '6' || s[*i] == '7'  || s[*i] == '8' || s[*i] == '9' || s[*i] == '0' || s[*i] == 'y' || s[*i] == 'u' || s[*i] == 'i' || s[*i] == 'o' || s[*i] == 'p' || s[*i] == 'h' || s[*i] == 'j' || s[*i] == 'k' || s[*i] == 'l' || s[*i] == ';' || s[*i] == 'n' || s[*i] == 'm' || s[*i] == ',' || s[*i] == '.') && (t[*j] == '6' || t[*j] == '7'  || t[*j] == '8' || t[*j] == '9' || t[*j] == '0' || t[*j] == 'y' || t[*j] == 'u' || t[*j] == 'i' || t[*j] == 'o' || t[*j] == 'p' || t[*j] == 'h' || t[*j] == 'j' || t[*j] == 'k' || t[*j] == 'l' || t[*j] == ';' || t[*j] == 'n' || t[*j] == 'm' || t[*j] == ',' || t[*j] == '.')) // right hand
        {
            insert_out(t[*j],*j);
            for(int a = strlen(s); a >= *i; a--)
            {
                s[a+1] = s[a];
            }
            s[*i] = t[*j];
                //d(k1,k2); TODO
        }
        //Inserting after another key on opposite hand - left to right
        else if(((s[*i] != t[*j]) && (s[*i-1] == t[*j-1]) && (t[*j+1] == s[*i])) && (s[*i] == '1' || s[*i] == '2'  || s[*i] == '3' || s[*i] == '3' || s[*i] == '4' || s[*i] == '5' || s[*i] == 'q' || s[*i] == 'w' || s[*i] == 'e' || s[*i] == 'r' || s[*i] == 't' || s[*i] == 'a' || s[*i] == 's' || s[*i] == 'd' || s[*i] == 'f' || s[*i] == 'g' || s[*i] == 'z' || s[*i] == 'x' || s[*i] == 'c' || s[*i] == 'v' || s[*i] == 'b') && (t[*j] == '6' || t[*j] == '7'  || t[*j] == '8' || t[*j] == '9' || t[*j] == '0' || t[*j] == 'y' || t[*j] == 'u' || t[*j] == 'i' || t[*j] == 'o' || t[*j] == 'p' || t[*j] == 'h' || t[*j] == 'j' || t[*j] == 'k' || t[*j] == 'l' || t[*j] == ';' || t[*j] == 'n' || t[*j] == 'm' || t[*j] == ',' || t[*j] == '.')) //left hand
        {
            insert_out(t[*j],*j);
            for(int a = strlen(s); a >= *i; a--)
            {
                s[a+1] = s[a];
            }
            s[*i] = t[*j];
            return 5;
        }
        //Inserting after another key on opposite hand - right to left
        else if(((s[*i] != t[*j]) && (s[*i-1] == t[*j-1]) && (t[*j+1] == s[*i])) && (s[*i] == '6' || s[*i] == '7'  || s[*i] == '8' || s[*i] == '9' || s[*i] == '0' || s[*i] == 'y' || s[*i] == 'u' || s[*i] == 'i' || s[*i] == 'o' || s[*i] == 'p' || s[*i] == 'h' || s[*i] == 'j' || s[*i] == 'k' || s[*i] == 'l' || s[*i] == ';' || s[*i] == 'n' || s[*i] == 'm' || s[*i] == ',' || s[*i] == '.') && (t[*j] == '1' || t[*j] == '2'  || t[*j] == '3' || t[*j] == '3' || t[*j] == '4' || t[*j] == '5' || t[*j] == 'q' || t[*j] == 'w' || t[*j] == 'e' || t[*j] == 'r' || t[*j] == 't' || t[*j] == 'a' || t[*j] == 's' || t[*j] == 'd' || t[*j] == 'f' || t[*j] == 'g' || t[*j] == 'z' || t[*j] == 'x' || t[*j] == 'c' || t[*j] == 'v' || t[*j] == 'b')) // right hand
        {
            insert_out(t[*j],*j);
            for(int a = strlen(s); a >= *i; a--)
            {
                s[a+1] = s[a];
            }
            s[*i] = t[*j];
            return (5);
        }
    }
}

int del ( char *s, char *t, int *i, int *j )
{
    if((*i == *j) && (s[*i] != t[*j]) && (s[*i] != t[*j+1]))
    {   
        //Deleting Repeated Character
        if((s[*i-1] == t[*j-1]) && (s[*i-1] == s[*i]) && (s[*i] != t[*j])) 
        {
            delete_out(*s,*i);
            for(int a = *i; a < MAXLEN; a++)
            {
                s[a] = s[a+1];
            }
            return 1;
        }
        //Deleting Space 
        else if ((s[*i-1] == ' ') && (t[*j-1] == s[*i]) && (t[*j] != s[*i])) 
        {
            delete_out(*s,*i);
            for(int a = *i; a < MAXLEN; a++)
            {
                s[a] = s[a+1];
            }
            return 3;
        } 
        //Deleting character after another key on same hand TODO
        else if((s[*i-1] == t[*j-1]) && (s[*i+1] == t[*j]) && (s[*i] != t[*j]) && (s[*i-1] == '1' || s[*i-1] == '2'  || s[*i-1] == '3' || s[*i-1] == '3' || s[*i-1] == '4' || s[*i-1] == '5' || s[*i-1] == 'q' || s[*i-1] == 'w' || s[*i-1] == 'e' || s[*i-1] == 'r' || s[*i-1] == 't' || s[*i-1] == 'a' || s[*i-1] == 's' || s[*i-1] == 'd' || s[*i-1] == 'f' || s[*i-1] == 'g' || s[*i-1] == 'z' || s[*i-1] == 'x' || s[*i-1] == 'c' || s[*i-1] == 'v' || s[*i-1] == 'b')) //left hand
        {
            if((s[*i] == '1' || s[*i] == '2'  || s[*i] == '3' || s[*i] == '3' || s[*i] == '4' || s[*i] == '5' || s[*i] == 'q' || s[*i] == 'w' || s[*i] == 'e' || s[*i] == 'r' || s[*i] == 't' || s[*i] == 'a' || s[*i] == 's' || s[*i] == 'd' || s[*i] == 'f' || s[*i] == 'g' || s[*i] == 'z' || s[*i] == 'x' || s[*i] == 'c' || s[*i] == 'v' || s[*i] == 'b'))
            {
                delete_out(*s,*i);
                for(int a = *i; a < MAXLEN; a++)
                {
                s[a] = s[a+1];
                }
                return 2;
            }
        	//Deleting character after space or key on different hand TODO
            else if((s[*i] != t[*j]) && (s[*i-1] == ' ') && (s[*i-1] == t[*j-1])) // 
            {
                delete_out(*s,*i);
                for(int a = *i; a < MAXLEN; a++)
                {
                    s[a] = s[a+1];
                }
                return 6;
            }
        }
        else if(((s[*i-1] == '1' || s[*i-1] == '2'  || s[*i-1] == '3' || s[*i-1] == '3' || s[*i-1] == '4' || s[*i-1] == '5' || s[*i-1] == 'q' || s[*i-1] == 'w' || s[*i-1] == 'e' || s[*i-1] == 'r' || s[*i-1] == 't' || s[*i-1] == 'a' || s[*i-1] == 's' || s[*i-1] == 'd' || s[*i-1] == 'f' || s[*i-1] == 'g' || s[*i-1] == 'z' || s[*i-1] == 'x' || s[*i-1] == 'c' || s[*i-1] == 'v' || s[*i-1] == 'b')) && (s[*i] == '1' || s[*i] == '2'  || s[*i] == '3' || s[*i] == '3' || s[*i] == '4' || s[*i] == '5' || s[*i] == 'q' || s[*i] == 'w' || s[*i] == 'e' || s[*i] == 'r' || s[*i] == 't' || s[*i] == 'a' || s[*i] == 's' || s[*i] == 'd' || s[*i] == 'f' || s[*i] == 'g' || s[*i] == 'z' || s[*i] == 'x' || s[*i] == 'c' || s[*i] == 'v' || s[*i] == 'b'))
        {
            delete_out(*s,*i);
            for(int a = *i; a < MAXLEN; a++)
            {
                s[a] = s[a+1];
            }
            return 6;
        }
        else if((s[*i-1] == t[*j-1]) && (s[*i+1] == t[*j]) && (s[*i] != t[*j]) && (s[*i-1] == '6' || s[*i-1] == '7'  || s[*i-1] == '8' || s[*i-1] == '9' || s[*i-1] == '0' || s[*i-1] == 'y' || s[*i-1] == 'u' || s[*i-1] == 'i' || s[*i-1] == 'o' || s[*i-1] == 'p' || s[*i-1] == 'h' || s[*i-1] == 'j' || s[*i-1] == 'k' || s[*i-1] == 'l' || s[*i-1] == ';' || s[*i-1] == 'n' || s[*i-1] == 'm' || s[*i-1] == ',' || s[*i-1] == '.')) // right hand
        {
            if((s[*i] != t[*j]) && (s[*i] == '6' || s[*i] == '7'  || s[*i] == '8' || s[*i] == '9' || s[*i] == '0' || s[*i] == 'y' || s[*i] == 'u' || s[*i] == 'i' || s[*i] == 'o' || s[*i] == 'p' || s[*i] == 'h' || s[*i] == 'j' || s[*i] == 'k' || s[*i] == 'l' || s[*i] == ';' || s[*i] == 'n' || s[*i] == 'm' || s[*i] == ',' || s[*i] == '.'))//delete character after key on same hand TODO
            {
                delete_out(*s,*i);
                for(int a = *i; a < MAXLEN; a++)
                {
                    s[a] = s[a+1];
                }
                return 2;
            }
            else if(((s[*i] == t[*j])) || (s[*i] == '1' || s[*i] == '2'  || s[*i] == '3' || s[*i] == '3' || s[*i] == '4' || s[*i] == '5' || s[*i] == 'q' || s[*i] == 'w' || s[*i] == 'e' || s[*i] == 'r' || s[*i] == 't' || s[*i] == 'a' || s[*i] == 's' || s[*i] == 'd' || s[*i] == 'f' || s[*i] == 'g' || s[*i] == 'z' || s[*i] == 'x' || s[*i] == 'c' || s[*i] == 'v' || s[*i] == 'b')) //character after space or key on diff hand
            {
                delete_out(*s,*i);
                for(int a = *i; a < MAXLEN; a++)
                {
                s[a] = s[a+1];
                }
                return 6;
            }
        }
        //Deleting first character in string
        else if((s[*i-1] != t[*j-1]) && *i == 1 && *j == 1) 
        {
            delete_out(*s,*i);
            for(int a = *i; a < MAXLEN; a++)
            {
                s[a] = s[a+1];
            }
            return 6;
        }
    }
}

int sub ( char *s, char *t, int *i, int *j )
{
	if((*i == *j) && (s[*i] != t[*j]) && (s[*i] != t[*j+1]) && (s[*i] != t[*j-1]))
	{
		//Space for anything or anything for space
    	if(((s[*i] != ' ' && t[*j] == ' ') || (s[*i] == ' ' && t[*j] != ' '))) 
        {
        	sub_out(t[*j],*i);
        	s[*i] = t[*j];
        	return 6;
        }
        //Substituting key for another on same hand  - left hand
        else if(((s[*i] == '1' && t[*j] != '1') || (s[*i] == '2' && t[*j] != '2')  || (s[*i] == '3' && t[*j] != '3') || (s[*i] == '4' && t[*j] != '4') || (s[*i] == '5' && t[*j] != '5') || (s[*i] == 'q' && t[*j] != 'q') || (s[*i] == 'w' && t[*j] != 'w') || (s[*i] == 'e' && t[*j] != 'e') || (s[*i] == 'r' && t[*j] != 'r') || (s[*i] == 't' && t[*j] != 't') || (s[*i] == 'a' && t[*j] != 'a') || (s[*i] == 's' && t[*j] != 's') || (s[*i] == 'd' && t[*j] != 'd') || (s[*i] == 'f' && t[*j] != 'f') || (s[*i] == 'g' && t[*j] != 'g') || (s[*i] == 'z' && t[*j] != 'z') || (s[*i] == 'x' && t[*j] != 'x') || (s[*i] == 'c' && t[*j] != 'c') || (s[*i] == 'v' && t[*j] != 'v') || (s[*i] == 'b' && t[*j] != 'b')))
    	{
    		if(((t[*j] == '1' && s[*i] != '1') || t[*j] == '2' && s[*i] != '2') || (t[*j] == '3' && s[*i] != '3') || (t[*j] == '4' && s[*i] != '4') || (t[*j] == '5' && s[*i] != '5') || (t[*j] == 'q' && s[*i] != 'q') || (t[*j] == 'w' && s[*i] != 'w') || (t[*j] == 'e' && s[*i] != 'e') || (t[*j] == 'r' && s[*i] != 'r') || (t[*j] == 't' && s[*i] != 't') || (t[*j] == 'a' && s[*i] != 'a') || (t[*j] == 's' && s[*i] != 's') || (t[*j] == 'd' && s[*i] != 'd') || (t[*j] == 'f' && s[*i] != 'f') || (t[*j] == 'g' && s[*i] != 'g') || (t[*j] == 'z' && s[*i] != 'z') || (t[*j] == 'x' && s[*i] != 'x') || (t[*j] == 'c' && s[*i] != 'c') || (t[*j] == 'v' && s[*i] != 'v') || (t[*j] == 'b' && s[*i] != 'b'))
    		{
				sub_out(t[*j],*i);
				s[*i] = t[*j];
    			//return d(k1,k2); TODO
    		}
    	}
    	//Substituting key for another on same hand - right hand
    	else if(((s[*i] == '6' && t[*j] != '6') || (s[*i] == '7' && t[*j] != '7') || (s[*i] == '8' && t[*j] != '8') || (s[*i] == '9' && t[*j] != '9') || (s[*i] == '0' && t[*j] != '0') || (s[*i] == 'y' && t[*j] != 'y') || (s[*i] == 'u' && t[*j] != 'u') || (s[*i] == 'i' && t[*j] != 'i') || (s[*i] == 'o' && t[*j] != 'o') || (s[*i] == 'p' && t[*j] != 'p') || (s[*i] == 'h' && t[*j] != 'h') || (s[*i] == 'j' && t[*j] != 'j') || (s[*i] == 'k' && t[*j] != 'k') || (s[*i] == 'l' && t[*j] != 'l') || (s[*i] == ';' && t[*j] != ';') || (s[*i] == 'n' && t[*j] != 'n') || (s[*i] == 'm' && t[*j] != 'm') || (s[*i] == ',' && t[*j] != ',') || (s[*i] == '.' && t[*j] != '.')))
    	{
    		if(((t[*j] == '6' && s[*i] != '6') || (t[*j] == '7' && s[*i] != '7') || (t[*j] == '8' && s[*i] != '8') || (t[*j] == '9' && s[*i] != '9') || (t[*j] == '0' && s[*i] != '0') || (t[*j] == 'y' && s[*i] != 'y') || (t[*j] == 'u' && s[*i] != 'u') || (t[*j] == 'i' && s[*i] != 'i') || (t[*j] == 'o' && s[*i] != 'o') || (t[*j] == 'p' && s[*i] != 'p') || (t[*j] == 'h' && s[*i] != 'h') || (t[*j] == 'j' && s[*i] != 'j') || (t[*j] == 'k' && s[*i] != 'k') || (t[*j] == 'l' && s[*i] != 'l') || (t[*j] == ';' && s[*i] != ';') || (t[*j] == 'n' && s[*i] != 'n') || (t[*j] == 'm' && s[*i] != 'm') || (t[*j] == ',' && s[*i] != ',') || (t[*j] == '.' && s[*i] != '.')))
    		{
				sub_out(t[*j],*i);
				s[*i] = t[*j];
    			//return d(k1,k2); TODO
    		}
    	}
        	//Substituting key for another on same finger other hand pinky finger
		if(s[*i] != t[*j])
		{
			if((s[*i] == 'q' || s[*i] == 'a' || s[*i] == 'z' || s[*i] == '1') || ((s[*i] == 'p' || s[*i] == ';' || s[*i] == '0'))) 
			{
				if((((t[*j] == 'p' || t[*j] == ';' || t[*j] == '0') && (s[*i] != 'p' || s[*i] != ';' || s[*i] != '0')) || ((t[*j] == 'q' || t[*j] == 'a' || t[*j] == 'z' || t[*j] == '1') && (s[*i] != 'q' || s[*i] != 'a' || s[*i] != 'z' || s[*i] != '1')) ))
				{
					sub_out(t[*j],*i);
					s[*i] = t[*j];
					return 1;	
				}
			}
			//Substituting key for another on same finger other hand ring finger
			else if((s[*i] == 'w' || s[*i] == 's' || s[*i] == 'x' || s[*i] == '2') || ((s[*i] == 'o' || s[*i] == 'l' || s[*i] == '.' || s[*i] == '9'))) 
			{
				if((((t[*j] == 'o' || t[*j] == 'l' || t[*j] == '.' || t[*j] == '2') && (s[*i] != 'o' || s[*i] != 'l' || s[*i] != '.' || s[*i] != '2')) || ((t[*j] == 'w' || t[*j] == 's' || t[*j] == 'x' || t[*j] == '9') && (s[*i] != 'w' || s[*i] != 's' || s[*i] != 'x' || s[*i] != '9'))))
				{
					sub_out(t[*j],*i);
					s[*i] = t[*j];
					return 1;	
				}
			}
			//Substituting key for another on same finger other hand middle finger
			else if((s[*i] == 'e' || s[*i] == 'd' || s[*i] == 'c' || s[*i] == '3') || ((s[*i] == 'i' || s[*i] == 'k' || s[*i] == ',' || s[*i] == '8'))) 
			{
				if((((t[*j] == 'i' || t[*j] == 'k' || t[*j] == ',' || t[*j] == '8') && (s[*i] != 'i' || s[*i] != 'k' || s[*i] != ',' || s[*i] != '8')) || ((t[*j] == 'e' || t[*j] == 'd' || t[*j] == 'c' || t[*j] == '3') && (s[*i] != 'e' || s[*i] != 'd' || s[*i] != 'c' || s[*i] != '3'))))
				{
					sub_out(t[*j],*i);
               		s[*i] = t[*j];
					return 1;	
				}
			}
			//Substituting key for another on same finger other hand index finger
			else if((s[*i] == 'r' || s[*i] == 'f' || s[*i] == 'v' || s[*i] == 't' || s[*i] == 'g' || s[*i] == 'b' || s[*i] == '4' || s[*i] == '5') || ((s[*i] == 'y' || s[*i] == 'h' || s[*i] == 'n' || s[*i] == 'u' || s[*i] == 'j' || s[*i] == 'm' || s[*i] == '6' || s[*i] == '7'))) 
			{
				if((((t[*j] == 'r' || t[*j] == 'f' || t[*j] == 'v' || t[*j] == 't' || t[*j] == 'g' || t[*j] == 'b' || t[*j] == '4' || t[*j] == '5') && (s[*i] != 'r' || s[*i] != 'f' || s[*i] != 'v' || s[*i] != 't' || s[*i] != 'g' || s[*i] != 'b' || s[*i] != '4' || s[*i] != '5')) || ((t[*j] == 'y' || t[*j] == 'h' || t[*j] == 'n' || t[*j] == 'u' || t[*j] == 'j' || t[*j] == 'm' || t[*j] == '6' || t[*j] == '7') && (s[*i] != 'y' || s[*i] != 'h' || s[*i] != 'n' || s[*i] != 'u' || s[*i] != 'j' || s[*i] != 'm' || s[*i] != '6' || s[*i] != '7'))))
				{
					sub_out(t[*j],*i);
					s[*i] = t[*j];
					return 1;	
				}
			}
			////Substituting key for another on different finger other hand pinky finger
			if((s[*i] == 'q' || s[*i] == 'a' || s[*i] == 'z' || s[*i] == '1') || ((s[*i] == 'p' || s[*i] == ';' || s[*i] == '0'))) 
			{
				if((((t[*j] != 'p' || t[*j] != ';' || t[*j] != '0') && (s[*i] != 'p' || s[*i] != ';' || s[*i] != '0')) || ((t[*j] != 'q' || t[*j] != 'a' || t[*j] != 'z' || t[*j] != '1') && (s[*i] != 'q' || s[*i] != 'a' || s[*i] != 'z' || s[*i] != '1'))))
				{
					sub_out(s[*i],*i);
					s[*i] = t[*j];
					return 5;	
				}
			}
			//Substituting key for another on different finger other hand ring finger
			else if((s[*i] == 'w' || s[*i] == 's' || s[*i] == 'x' || s[*i] == '2') || ((s[*i] == 'o' || s[*i] == 'l' || s[*i] == '.' || s[*i] == '9'))) 
			{
				if((((t[*j] != 'o' || t[*j] != 'l' || t[*j] != '.' || t[*j] != '2') && (s[*i] != 'o' || s[*i] != 'l' || s[*i] != '.' || s[*i] != '2')) || ((t[*j] != 'w' || t[*j] != 's' || t[*j] != 'x' || t[*j] != '9') && (s[*i] != 'w' || s[*i] != 's' || s[*i] != 'x' || s[*i] != '9'))))
				{
					sub_out(t[*j],*i);
					s[*i] = t[*j];
					return 5;	
				}
			}
			//Substituting key for another on different finger other hand middle finger 
			else if((s[*i] == 'e' || s[*i] == 'd' || s[*i] == 'c' || s[*i] == '3') || ((s[*i] == 'i' || s[*i] == 'k' || s[*i] == ',' || s[*i] == '8'))) 
			{
				if((((t[*j] != 'i' || t[*j] != 'k' || t[*j] != ',' || t[*j] != '8') && (s[*i] != 'i' || s[*i] != 'k' || s[*i] != ',' || s[*i] != '8')) || ((t[*j] != 'e' || t[*j] != 'd' || t[*j] != 'c' || t[*j] != '3') && (s[*i] != 'e' || s[*i] != 'd' || s[*i] != 'c' || s[*i] != '3'))))
				{
					sub_out(t[*j],*i);
					s[*i] = t[*j];
					return 5;	
				}
			}
			//Substituting key for another on different finger other hand index finger
			else if((s[*i] == 'r' || s[*i] == 'f' || s[*i] == 'v' || s[*i] == 't' || s[*i] == 'g' || s[*i] == 'b' || s[*i] == '4' || s[*i] == '5') || ((s[*i] == 'y' || s[*i] == 'h' || s[*i] == 'n' || s[*i] == 'u' || s[*i] == 'j' || s[*i] == 'm' || s[*i] == '6' || s[*i] == '7'))) 
			{
				if((((t[*j] != 'r' || t[*j] != 'f' || t[*j] != 'v' || t[*j] != 't' || t[*j] != 'g' || t[*j] != 'b' || t[*j] != '4' || t[*j] != '5') && (s[*i] != 'r' || s[*i] != 'f' || s[*i] != 'v' || s[*i] != 't' || s[*i] != 'g' || s[*i] != 'b' || s[*i] != '4' || s[*i] != '5')) || ((t[*j] != 'y' || t[*j] != 'h' || t[*j] != 'n' || t[*j] != 'u' || t[*j] != 'j' || t[*j] != 'm' || t[*j] != '6' || t[*j] != '7') && (s[*i] != 'y' || s[*i] != 'h' || s[*i] != 'n' || s[*i] != 'u' || s[*i] != 'j' || s[*i] != 'm' || s[*i] != '6' || s[*i] != '7')))) 
				{
					sub_out(t[*j],*i);
					s[*i] = t[*j];
					return 5;
				}
			}
		}
	}
}

int trans ( char *s, char *t, int *i, int *j )
{
	char temp = ' ';
    if ( !( (*i < MAXLEN) && (*j < MAXLEN) ))
    {
        return 10;
    }
	// Transposing space with anything else
    if ( s[*i] == t[(*j)-1] && s[(*i)-1] == t[*j] && (s[*i] != s[(*i)-1]) && (*i == *j) )
    {
    	if(((s[*i] == ' ') && (t[*j] != s[*i])) || ((s[*i-1] == ' ') && (t[*j-1] != s[*i-1])))
		{
			trans_out(*s,*t,*i,*j);
			temp = s[*i];
            s[*i] = s[*i-1];
            s[*i-1] = temp;
			return 3;
		}
		//Transposing keys on differing hands left to right
        else if((s[*i-1] == '1' || s[*i-1] == '2'  || s[*i-1] == '3' || s[*i-1] == '3' || s[*i-1] == '4' || s[*i-1] == '5' || s[*i-1] == 'q' || s[*i-1] == 'w' || s[*i-1] == 'e' || s[*i-1] == 'r' || s[*i-1] == 't' || s[*i-1] == 'a' || s[*i-1] == 's' || s[*i-1] == 'd' || s[*i-1] == 'f' || s[*i-1] == 'g' || s[*i-1] == 'z' || s[*i-1] == 'x' || s[*i-1] == 'c' || s[*i-1] == 'v' || s[*i-1] == 'b') && (s[*i] == '6' || s[*i] == '7'  || s[*i] == '8' || s[*i] == '9' || s[*i] == '0' || s[*i] == 'y' || s[*i] == 'u' || s[*i] == 'i' || s[*i] == 'o' || s[*i] == 'p' || s[*i] == 'h' || s[*i] == 'j' || s[*i] == 'k' || s[*i] == 'l' || s[*i] == ';' || s[*i] == 'n' || s[*i] == 'm' || s[*i] == ',' || s[*i] == '.'))
    	{
    		trans_out(*s,*t,*i,*j);
    		temp = s[*i];
            s[*i] = s[*i-1];
            s[*i-1] = temp;
			return 1;
    	}
    	//Transposing keys on differing hands right to left 
    	else if((s[*i-1] == '6' || s[*i-1] == '7'  || s[*i-1] == '8' || s[*i-1] == '9' || s[*i-1] == '0' || s[*i-1] == 'y' || s[*i-1] == 'u' || s[*i-1] == 'i' || s[*i-1] == 'o' || s[*i-1] == 'p' || s[*i-1] == 'h' || s[*i-1] == 'j' || s[*i-1] == 'k' || s[*i-1] == 'l' || s[*i-1] == ';' || s[*i-1] == 'n' || s[*i-1] == 'm' || s[*i-1] == ',' || s[*i-1] == '.') && (s[*i] == '1' || s[*i] == '2'  || s[*i] == '3' || s[*i] == '3' || s[*i] == '4' || s[*i] == '5' || s[*i] == 'q' || s[*i] == 'w' || s[*i] == 'e' || s[*i] == 'r' || s[*i] == 't' || s[*i] == 'a' || s[*i] == 's' || s[*i] == 'd' || s[*i] == 'f' || s[*i] == 'g' || s[*i] == 'z' || s[*i] == 'x' || s[*i] == 'c' || s[*i] == 'v' || s[*i] == 'b'))
    	{
    		trans_out(*s,*t,*i,*j);
    		temp = s[*i];
            s[*i] = s[*i-1];
            s[*i-1] = temp;
			return 1;
    	}
    	//Transposing keys on the same hand left and left 
    	else if ((s[*i-1] == '1' || s[*i-1] == '2'  || s[*i-1] == '3' || s[*i-1] == '3' || s[*i-1] == '4' || s[*i-1] == '5' || s[*i-1] == 'q' || s[*i-1] == 'w' || s[*i-1] == 'e' || s[*i-1] == 'r' || s[*i-1] == 't' || s[*i-1] == 'a' || s[*i-1] == 's' || s[*i-1] == 'd' || s[*i-1] == 'f' || s[*i-1] == 'g' || s[*i-1] == 'z' || s[*i-1] == 'x' || s[*i-1] == 'c' || s[*i-1] == 'v' || s[*i-1] == 'b') && (s[*i] == '1' || s[*i] == '2'  || s[*i] == '3' || s[*i] == '3' || s[*i] == '4' || s[*i] == '5' || s[*i] == 'q' || s[*i] == 'w' || s[*i] == 'e' || s[*i] == 'r' || s[*i] == 't' || s[*i] == 'a' || s[*i] == 's' || s[*i] == 'd' || s[*i] == 'f' || s[*i] == 'g' || s[*i] == 'z' || s[*i] == 'x' || s[*i] == 'c' || s[*i] == 'v' || s[*i] == 'b'))
    	{
    		trans_out(*s,*t,*i,*j);
    		temp = s[*i];
            s[*i] = s[*i-1];
            s[*i-1] = temp;
			return 2;
    	}
    	//Transposing keys on the same hand right and right
    	else if ((s[*i] == '6' || s[*i] == '7'  || s[*i] == '8' || s[*i] == '9' || s[*i] == '0' || s[*i] == 'y' || s[*i] == 'u' || s[*i] == 'i' || s[*i] == 'o' || s[*i] == 'p' || s[*i] == 'h' || s[*i] == 'j' || s[*i] == 'k' || s[*i] == 'l' || s[*i] == ';' || s[*i] == 'n' || s[*i] == 'm' || s[*i] == ',' || s[*i] == '.') && (s[*i-1] == '6' || s[*i-1] == '7'  || s[*i-1] == '8' || s[*i-1] == '9' || s[*i-1] == '0' || s[*i-1] == 'y' || s[*i-1] == 'u' || s[*i-1] == 'i' || s[*i-1] == 'o' || s[*i-1] == 'p' || s[*i-1] == 'h' || s[*i-1] == 'j' || s[*i-1] == 'k' || s[*i-1] == 'l' || s[*i-1] == ';' || s[*i-1] == 'n' || s[*i-1] == 'm' || s[*i-1] == ',' || s[*i-1] == '.'))
    	{
    		trans_out(*s,*t,*i,*j);
    		temp = s[*i];
            s[*i] = s[*i-1];
            s[*i-1] = temp;
			return 2;
    	}
    }
}

int string_edit_distance (char *s, char *t)
{
    int i, j;
    int first = 0;
    int opt[5];             /* cost of the options */
    for (unsigned int i=0; i < MAXLEN; i++)
    {
        row_init(i);
        column_init(i);
    }

    for (i=1; i < (int) strlen(s); i++) 
    {
        for (j=1; j < (int) strlen(t); j++) 
        {
            opt[MATCH]  = m[i-1][j-1].cost + match(s[i],t[j]);
            opt[INSERT] = m[i][j-1].cost   + insert(s,t,&i,&j);
            opt[DELETE] = m[i-1][j].cost   + del(s,t,&i,&j);
            opt[SUB]    = m[i][j].cost     + sub(s,t,&i,&j);
            opt[TRANS]  = m[i-1][j-1].cost + trans(s,t,&i,&j);

            m[i][j].cost = opt[MATCH];
            m[i][j].parent = MATCH;
            for (int k=INSERT; k<=TRANS; k++)
            {   
            	if (opt[k] < m[i][j].cost) 
            	{
                    m[i][j].cost = opt[k];
                    m[i][j].parent = k;
                    if ( k == TRANS ) 
                    {
                        m[i][j].cost += 1;
                        m[i][j].parent = k;
                        ++i, ++j;
                        m[i][j].cost = m[i-1][j-1].cost + 1;
                        m[i][j].parent = k;
                    }
                }
            }
        }
    }
	
    goal_cell(s,t,&i,&j);
    return( m[i][j].cost );
}

/*********** main ***********/
int main () 
{
    string target = "";
    string typo = "";
    string junk = "";
    int loopCount = 0;
    
    ifstream input("input.txt"); //sets the input stream to input file
    ofstream myfile("output.txt"); //sets output stream to output file
    if (input.is_open())
    {
        input >> loopCount;
        getline(input, junk);
        while(loopCount > 0)
        {
            getline(input, junk);
            getline(input, target);
            getline(input, typo);
            char *newtar = new char[target.length() + 1];
            char *newtypo = new char[typo.length() + 1];
            strcpy(newtar, target.c_str());
            strcpy(newtypo, typo.c_str());
            string_edit_distance(newtar,newtypo);// << endl;
            loopCount--;
            delete [] newtar;
            delete [] newtypo;
        }
    }
    return 0;
}
