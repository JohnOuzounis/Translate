#include <stdio.h>
#include <stdlib.h>

typedef enum State
{
	ANY_STATE,
	N_STATE,
	NCAP_STATE,
	M_STATE,
	MCAP_STATE
} State;

int IsNormal(int c)
{
	/* Greek letters:
	   { α,Α, β,Β, γ,Γ, δ,Δ, ε,Ε, ζ,Ζ,
		 η,Η, θ,Θ, ι,Ι, κ,Κ, λ,Λ, μ,Μ,
		 ν,Ν, ο,Ο, π,Π, ρ,Ρ, ς,σ,Σ, τ,Τ
		 υ,Υ, φ,Φ, χ,Χ, ω,Ω }
	*/
	int greek[45] = {225, 193, 226, 194, 227, 195, 228, 196, 229, 197, 230, 198,
					 231, 199, 232, 200, 233, 201, 234, 202, 235, 203, 236, 204,
					 237, 205, 239, 207, 240, 208, 241, 209, 242, 243, 211, 244, 212,
					 245, 213, 246, 214, 247, 215, 249, 217};

	int i;
	for (i = 0; i < 45; i++)
		if (greek[i] == c)
			return i;
	return -1;
}

int IsDiphthong(int c)
{
	// diphthong greek letters: {ξ,Ξ, ψ,Ψ}
	int diphthong[4] = {238, 206, 248, 216};
	int i;
	for (i = 0; i < 4; i++)
		if (diphthong[i] == c)
			return i;
	return -1;
}

int IsStressed(int c)
{
	// stressed greek letters: { Ά,ά, Έ,έ, Ή,ή, Ί, ί,Ό,ό, Ώ,ώ, Ύ,ύ}
	int stressed[14] = {182, 220, 184, 221, 185, 222, 186,
						223, 188, 252, 191, 254, 190, 253};
	int i;
	for (i = 0; i < 14; i++)
		if (stressed[i] == c)
			return i;
	return -1;
}

int IsUmlauted(int c)
{
	// umlauted greek letters: { ϊ,ΐ,Ϊ, ϋ,ΰ,Ϋ}
	int umlauted[6] = {250, 192, 218, 251, 224, 219};
	int i;
	for (i = 0; i < 6; i++)
		if (umlauted[i] == c)
			return i;
	return -1;
}

int *getIndexTable(int c)
{
	int *indexes = malloc(2 * sizeof(int));
	indexes[0] = -1;
	indexes[1] = -1;

	const int len = 4;
	int (*f_checkType[4])(int) = {&IsNormal, &IsStressed, &IsDiphthong, &IsUmlauted};

	for (int i = 0; i < len; i++)
	{
		int index = (*f_checkType[i])(c);

		if (index != -1)
		{
			indexes[0] = i, indexes[1] = index;
			break;
		}
	}

	return indexes;
}

void printChar(int c)
{
	char *eng_diphthong[4] = {"ks", "KS", "ps", "PS"};
	char *eng_umlauted[6] = {"i\"", "i'\"", "I\"", "y\"", "y'\"", "Y\""};
	char *eng_stressed[14] = {"'A", "a'", "'E", "e'", "'H", "h'", "'I",
							  "i'", "'O", "o'", "'W", "w'", "'Y", "y'"};
	char *english[45] = {"a", "A", "v", "V", "g", "G", "d", "D", "e", "E", "z", "Z",
						 "h", "H", "8", "8", "i", "I", "k", "K", "l", "L", "m", "M",
						 "n", "N", "o", "O", "p", "P", "r", "R", "s", "s", "S", "t", "T",
						 "y", "Y", "f", "F", "x", "X", "w", "W"};

	char **printTable[] = {english, eng_stressed, eng_diphthong, eng_umlauted};

	int *indexes = getIndexTable(c);
	if (indexes[0] != -1)
	{
		printf("%s", printTable[indexes[0]][indexes[1]]);
	}
	else
	{

		putchar(c);
	}

	free(indexes);
}

State f_AnyState(int c)
{
	if (c == 237)
		return N_STATE;

	if (c == 205)
		return NCAP_STATE;

	if (c == 236)
		return M_STATE;

	if (c == 204)
		return MCAP_STATE;

	printChar(c);
	return ANY_STATE;
}

State gotoState(char normal, char special, int c, int lowerCase, int upperCase)
{
	if ((c == lowerCase) | (c == upperCase))
	{
		putchar(special);
		return ANY_STATE;
	}

	putchar(normal);
	return f_AnyState(c);
}

State f_NState(int c)
{
	return gotoState('n', 'd', c, 244, 212); // check t or T
}

State f_NCAPState(int c)
{
	return gotoState('N', 'D', c, 244, 212); // check t or T
}

State f_MState(int c)
{
	return gotoState('m', 'b', c, 240, 208); // check p or P
}

State f_MCAPState(int c)
{
	return gotoState('M', 'B', c, 240, 208); // check p or P
}

int main()
{
	State (*f_State[5])(int) = {&f_AnyState, &f_NState, &f_NCAPState, &f_MState, &f_MCAPState};
	State currentState = ANY_STATE;

	int c;
	while ((c = getchar()) != EOF)
	{
		currentState = (*f_State[currentState])(c);
	}
	return 0;
}
