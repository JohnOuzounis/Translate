#include<stdio.h>

typedef enum State {ANY_STATE, N_STATE, NCAP_STATE, M_STATE, MCAP_STATE} State;

/* This function takes as arguments an integer
   and checks if that integer is a representation
   of lower or upper case greek letters (excluding diphthong letters).

   Returns an integer indicating the position in the array the match was found
   or -1 in case it doesnt match any greek letters
*/
int IsNormal(int c){

	/* This array contains and integer representation of both lower and upper case greek letters
	   Specifically in the following order:
	   { α,Α, β,Β, γ,Γ, δ,Δ, ε,Ε, ζ,Ζ, 
	     η,Η, θ,Θ, ι,Ι, κ,Κ, λ,Λ, μ,Μ,
	     ν,Ν, ο,Ο, π,Π, ρ,Ρ, ς,σ,Σ, τ,Τ
	     υ,Υ, φ,Φ, χ,Χ, ω,Ω }
	*/
	int greek[45] = {225,193, 226,194, 227,195, 228,196, 229,197, 230,198,
					 231,199, 232,200, 233,201, 234,202, 235,203, 236,204,
					 237,205, 239,207, 240,208, 241,209, 242,243,211, 244,212,
					 245,213, 246,214, 247,215, 249,217};
	int i;
	for (i = 0; i < 45; i++) if (greek[i] == c) return i;
	return -1;
}

/* This function takes as arguments an integer
   and checks if that integer is a representation
   of lower or upper case greek diphthong letters.

   Returns an integer indicating the position in the array the match was found
   or -1 in case it doesnt match any greek letters
*/
int IsDiphthong(int c){

	/* This array contains and integer representation
	   of both lower and upper case diphthong greek letters

	   Specifically in the following order: {ξ,Ξ, ψ,Ψ}
	*/
	int diphthong[4] = {238,206, 248,216};
	int i;
	for (i = 0; i < 4; i++) if (diphthong[i] == c) return i;
	return -1;
}


/* This function takes as arguments an integer
   and checks if that integer is a representation
   of lower or upper case stressed greek letters.

   Returns an integer indicating the position in the array the match was found
   or -1 in case it doesnt match any greek letters
*/
int IsStressed(int c){

	/* This array contains and integer representation
	   of both lower and upper case stressed greek letters

	   Specifically in the following order: 
	   { Ά,ά, Έ,έ, Ή,ή, Ί,
	   	 ί,Ό,ό, Ώ,ώ, Ύ,ύ}
	*/
	int stressed[14] = {182, 220, 184, 221, 185, 222, 186,
						223, 188, 252, 191, 254, 190, 253};
	int i;
	for (i = 0; i < 14; i++) if (stressed[i] == c) return i;
	return -1;
}


/* This function takes as arguments an integer
   and checks if that integer is a representation
   of lower or upper case umlauted greek letters.

   Returns an integer indicating the position in the array the match was found
   or -1 in case it doesnt match any greek letters
*/
int IsUmlauted(int c){

	/* This array contains and integer representation
	   of both lower and upper case stressed greek letters

	   Specifically in the following order: { ϊ,ΐ,Ϊ, ϋ,ΰ,Ϋ}
	*/
	int umlauted[6] = {250,192,218,  251,224,219};
	int i;
	for (i = 0; i < 6; i++) if (umlauted[i] == c) return i;
	return -1;
}

/* This function takes as arguments an integer
   and checks if that integer is a representation
   of lower or upper case greek letters.
   If the integer does represent a greek character
   an english 'equivelant' is printed else an ascii representation is printed.
*/
void printChar(int c){

	char english[45] = {'a','A', 'v','V', 'g','G', 'd','D', 'e','E', 'z','Z',
						'h','H', '8','8', 'i','I', 'k','K', 'l','L', 'm','M',
						'n','N', 'o','O', 'p','P', 'r','R', 's','s','S', 't','T',
						'y','Y', 'f','F', 'x','X', 'w','W'};

	char* eng_stressed[14] = {"'A","a'", "'E","e'", "'H","h'", "'I",
							  "i'","'O","o'", "'W","w'", "'Y", "y'"};
	char* eng_umlauted[6] = {"i\"","i'\"","I\"", "y\"","y'\"","Y\""};
	char* eng_diphthong[4] = {"ks","KS", "ps","PS"};

	int i;
	if ((i = IsNormal(c)) != -1)	{ printf("%c",english[i]); return;};
  	if ((i = IsStressed(c)) != -1)  { printf("%s",eng_stressed[i]); return;}
	if ((i = IsDiphthong(c)) != -1) { printf("%s",eng_diphthong[i]); return;}
	if ((i = IsUmlauted(c)) != -1)  { printf("%s",eng_umlauted[i]); return;}
	putchar(c);
}

State f_AnyState(int c){

	if (c == 237) return N_STATE;	 /* If integer is a representation of greek n -> goto N_STATE*/
	if (c == 205) return NCAP_STATE; /* If integer is a representation of greek N -> goto NCAP_STATE*/
	if (c == 236) return M_STATE; 	 /* If integer is a representation of greek m -> goto M_STATE*/
	if (c == 204) return MCAP_STATE; /* If integer is a representation of greek M -> goto MCAP_STATE*/
	printChar(c);			 /* Else print whatever that integer is*/
	return ANY_STATE;
}

State f_NState(int c){
	
	if ((c == 244) | (c == 212)) {   /* If integer is a representation of greek t or T print d*/
		putchar('d'); 
		return ANY_STATE;
	}
	putchar('n');		         /* Print whatever you remember*/
	
	if (c == 237) return N_STATE;    /* If integer is a representation of greek n -> goto N_STATE*/
	if (c == 205) return NCAP_STATE; /* If integer is a representation of greek N -> goto NCAP_STATE*/
	if (c == 236) return M_STATE;    /* If integer is a representation of greek m -> goto M_STATE*/
	if (c == 204) return MCAP_STATE; /* If integer is a representation of greek M -> goto MCAP_STATE*/
	printChar(c);                    /* Print whatever the integer is*/
	return ANY_STATE;
}

State f_NCAPState(int c){

	if ((c == 244) | (c == 212)){    /* If integer is a representation of greek t or T print D*/
		putchar('D');
		return ANY_STATE;
	}
	putchar('N');		         /* Print whatever you remember*/
	
	if (c == 237) return N_STATE;    /* If integer is a representation of greek n -> goto N_STATE*/
	if (c == 205) return NCAP_STATE; /* If integer is a representation of greek N -> goto NCAP_STATE*/
	if (c == 236) return M_STATE;    /* If integer is a representation of greek m -> goto M_STATE*/
	if (c == 204) return MCAP_STATE; /* If integer is a representation of greek M -> goto MCAP_STATE*/
	printChar(c);                    /* Print whatever the integer is*/
	return ANY_STATE;
}

State f_MState(int c){

	if ((c == 240) | (c == 208)) {   /* If integer is a representation of greek p or P print b*/
		putchar('b'); 
		return ANY_STATE;
	}
	putchar('m');			 /* Print whatever you remember*/

	if (c == 236) return M_STATE;    /* If integer is a representation of greek m -> goto M_STATE*/
	if (c == 204) return MCAP_STATE; /* If integer is a representation of greek M -> goto MCAP_STATE*/
	if (c == 237) return N_STATE;    /* If integer is a representation of greek n -> goto N_STATE*/
	if (c == 205) return NCAP_STATE; /* If integer is a representation of greek N -> goto NCAP_STATE*/
	printChar(c);                    /* Print whatever the integer is*/
	return ANY_STATE;
}

State f_MCAPState(int c){

	if ((c == 240) | (c == 208)) {   /* If integer is a representation of greek p or P print b*/
		putchar('B');
		return ANY_STATE;
	}
	putchar('M');			 /* Print whatever you remember*/
	
	if (c == 236) return M_STATE;    /* If integer is a representation of greek m -> goto M_STATE*/
	if (c == 204) return MCAP_STATE; /* If integer is a representation of greek M -> goto MCAP_STATE*/
	if (c == 237) return N_STATE;    /* If integer is a representation of greek n -> goto N_STATE*/
	if (c == 205) return NCAP_STATE; /* If integer is a representation of greek N -> goto NCAP_STATE*/
	printChar(c);			 /* Print whatever the integer is*/
	return ANY_STATE;
}

int main(){

	State (*f_State[5])(int) = {&f_AnyState, &f_NState, &f_NCAPState, &f_MState, &f_MCAPState};
	State currentState = ANY_STATE;

	int c;
	while ((c = getchar()) != EOF){
		currentState = (*f_State[currentState])(c);
	}
	return 0;
}
