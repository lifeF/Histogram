/*
|--------------------------------------|
|	UNIVERSITY OF PERADENIYA           |
|   DEPARTMENT OF COMPUTER ENGINEER    |
|--------------------------------------|	
	  Autor : Rathnayake R.M.K.D
	  Reg Num: E 14 287

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Structures++++++++
struct elementw {
	char  word[100];
	unsigned int  wordCount;
	unsigned int wordLength;
	float precentage;
	struct elementw * next;
};
struct elementc {
	char c;
	unsigned int charCount;
	float precentage;
	struct elementc * next;
};


typedef struct elementc nodec;//node for character list
typedef struct elementw nodew;//node for Word List
//FUNCTION
void insertWordlist(char Word[],int wordCount,nodew * head);
char * Process_Word(char word[],char * word_processed);
char Process_char(char tmpchar);
int count_w(char ** argv,int argc);
int count_c(char ** argv,int argc);
int count_l(char ** argv,int argc);
int Find_length_INDEX(char ** argv,int argc);
int readable_File_counter(char ** argv,int argc);
int isexcist_Word(nodew * head, char word[]);
int increse_Word_count(nodew * head, char word[]);
int PrintList(nodew * head);
int calculate_Presentage(nodew* nodew);
//For char List
int isCharExist(char tmpchar);
void insertCharlist(char * tmpchar,int charCount,nodec * headc);
//print graph
void print_Bar(int Max_Word_len,int Word_len,float precentage,char word[],float max_precentage,int Scaled);
void print_Spacing(char word[],int max_Word_len,int s);
void print_word_GRAPH(nodew * head,int length,int Scaled);

void reverse_word_list(nodew** head_ref);
void reverse_char_list(nodec** head_ref);

int MaxCountList(nodew * head);
void print_char_GRAPH(nodec * headc , int length,int Scaled);
void print_char_Bar(int Max_Word_len,int Word_len,float precentage,char c ,float max_precentage,int Scaled);
void print_char_Spacing(char c,int s);
int  MaxcharCountList(nodec * head);
int MaxWordLengthCnsdrLength(nodew * head,int length);
int count_scaled(char ** argv,int argc);

//====================================================================================
nodew * headw=NULL;// head of the Word list
nodec * headc=NULL;
nodew * current=NULL; // it is use to travel the list
nodec * currentc=NULL;

//main function ===================================================================
int main (int argc, char ** argv){
//if argument length less than 2 then print Error message
	int length=Find_length_INDEX(argv,argc);
	int length_value =atoi(argv[Find_length_INDEX(argv,argc)]);
	int k=0;
	int Scaled_count=count_scaled(argv,argc);
	int countw=count_w(argv,argc);
	int countc=count_c(argv,argc);
	int countl=count_l(argv,argc);
	int noOFreadFile=readable_File_counter(argv,argc);

//ERROR PART ===================================================================================================================================
	if(length>0){
		k=1;
	}

	int x=(countw+countc+countl+noOFreadFile+Scaled_count+k);

	if(x<argc){
		int index1=1;
		while(index1<argc)
		{
			FILE * ch;
			if(index1!=length){
				
				if(((strcmp("-w",argv[index1])!=0)&(strcmp("-c",argv[index1])!=0)&(strcmp("-l",argv[index1])!=0)&(strcmp("--scaled",argv[index1])!=0))&(fopen(argv[index1],"r")==NULL)&(argv[index1][0]=='-')){
					printf("Invalid options for [%s]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[index1]);
					return -1;
				}	
			}
			index1++;		

		}
		printf("Cannot open one or more given files\n");

		return -1;
	}


	if(((countl==1)&(!isdigit(argv[length][0])))|(countl>1)){
		printf("Invalid options for [%s]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[length-1]);
		return -1;
	}
	if(countl>0 & length_value==0){
		return -1;
	}
	if((countw>0) & (countc>0)){
		printf("[-c] and [-w] cannot use together\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
		return -1;
	}
	if(argc<2|noOFreadFile<2){
		printf("No input files were given\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
		return -1;
	}
	if(((countl==1)&(!isdigit(argv[length][0])))|(countl>1)){
		printf("Invalid options for [%s]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[length-1]);
		return -1;
	}
	
	// count useful argument give ane equal to the x
	
//==============================================================================================================================================

// Word link list Preparation========================================================================================================================
	if((countw>0)|(countc==0)){
		//read file and prepare the link list
	FILE * FileStream;
		char tmpword[100];
		char Pword[100];
		int i=1;//we need to read except the program compile File 
		//checking all argument value
		while(i<argc){
			//file can read then continue the program
			char* word_processed=(char *)malloc(100*sizeof(char));
			if(fopen(argv[i],"r")!=NULL){
				FileStream=fopen(argv[i],"r");
				//read the file
				while(fscanf(FileStream,"%s",tmpword)!=EOF){
						int ic=0;
						int j=0;
						while(tmpword[ic]!='\0'){
							if(isalpha(tmpword[ic])|isdigit(tmpword[ic])){
								Pword[j]=tolower(tmpword[ic]);
								j++;
							}
							ic++;
						}					
						if(strcmp(Pword,"")){
							
							if(isexcist_Word(headw,Pword)){
								increse_Word_count(headw,Pword);
								
							}
			
							else{
								insertWordlist(Pword,1,headw);
								
							}
	 						
						}
						int k=100;
						while(k>=0){
							Pword[k]='\0';
							k--;
						}

					}
					fclose(FileStream);
				}
			i++;
			

		}
		if(headw==NULL){
				printf("No data to process\n");
				return -1;
		}
		calculate_Presentage(headw);//calculate word presentage each word in link list
		reverse_word_list(&headw);//reverse the list
		length=atoi(argv[Find_length_INDEX(argv,argc)]);
		
		if(countl==0){
			print_word_GRAPH(headw,10,Scaled_count);
		}
		else{
			print_word_GRAPH(headw,length,Scaled_count);
		}
		
	}
//=============================================================================================================================================


//Char list Preparation========================================================================================================================
	if(count_c(argv,argc)>0){
		//read file and prepare the link list
		FILE * FileStream;
		int i=1;//we need to read except the program compile File 
			while(i<argc){//checking all argument value
			
				//file can read then continue the program
				if(fopen(argv[i],"r")!=NULL){
					char tmpchar;
					FileStream=fopen(argv[i],"r");
					//read the file
					while(fscanf(FileStream,"%c",&tmpchar)!=EOF){
					
						if(isdigit(tmpchar)|isalpha(tmpchar)){
									
							if(isCharExist(tolower(tmpchar))){	// the char exsist then increacse the count
								currentc=headc;
								while(currentc!=NULL){
									if(currentc->c==tolower(tmpchar)){
										(currentc->charCount)++;
									}
									currentc=currentc->next;
								}

								
							}
		
							else{	//not exsist the char then add char to shr list
								nodec * data =(nodec *) malloc(sizeof(nodec));
								data->c=tolower(tmpchar);
								data->charCount=1;
								data->next=headc;
								headc=data;
							}

						
						}
	 					
						
					}
					fclose(FileStream);
				}
				i++;
			}
		if(headc==NULL){//link list is empty no data to process print
				printf("No data to process\n");
				return -1;
		}

		//calculate char presentage
		currentc=headc;
		int full_Count_of_Char=0;
		while(currentc!=NULL){
			
				full_Count_of_Char+=(currentc->charCount);
					
		    currentc=currentc->next;
		}
		
		currentc=headc;
		while(currentc!=NULL){
			currentc->precentage=(float)(currentc->charCount)*100/full_Count_of_Char;
		    currentc=currentc->next;
		}
		reverse_char_list(&headc);// reverse list
		length=atoi(argv[Find_length_INDEX(argv,argc)]);
		if(count_l(argv,argc)==0){
			
			print_char_GRAPH(headc,10,Scaled_count);
		}
		else{

			print_char_GRAPH(headc,length,Scaled_count);
		}
		
		
	}
//==========================================================================================================================================
	return 0;
}
//==================================================================================================
//Function Define ==================================================================================
//this function find excist char in link list
int isCharExist(char tmpchar){
	currentc=headc;
	while(currentc!=NULL){
		
		if((currentc->c)==tmpchar){
			return 1;
		}
		currentc=currentc->next;
	}
	return 0;
}

//calculate the precentage of the each word in the list
int calculate_Presentage(nodew* nodew){
	current=headw;
	int full_Count_of_word=0;
	while(current!=NULL){
		full_Count_of_word+=current->wordCount;
		current=current->next;
	}

	current=headw;
	while(current!=NULL){
		current->precentage=(float)current->wordCount*100/full_Count_of_word;
		current=current->next;
	}
	return 1;
}

// insert data to the list
void insertWordlist(char Word[],int wordCount,nodew * head){

	nodew * data_holder=(nodew*)malloc(sizeof(nodew));//it use to make joint it work as a link
	strcpy(data_holder->word,Word);//latest head address link to current data holder next address
	data_holder->wordCount=wordCount;
	data_holder->wordLength=strlen(Word);
	data_holder->next=headw;
	headw=data_holder; 

}

//use to reverse the word linklist
void reverse_word_list(nodew** head_ref)
{
    nodew* prev   = NULL;
    nodew* current = *head_ref;
    nodew* next;
    while (current != NULL)
    {
        next  = current->next;  
        current->next = prev;   
        prev = current;
        current = next;
    }
    *head_ref = prev;
}
 
//use to reverse the char linklist
void reverse_char_list(nodec** head_ref)
{
    nodec* prev   = NULL;
    nodec* currentc = *head_ref;
    nodec* next;
    while (currentc != NULL)
    {
        next  = currentc->next;  
        currentc->next = prev;   
        prev = currentc;
        currentc = next;
    }
    *head_ref = prev;
}

//checking the word is excist in the link list 
int isexcist_Word(nodew * head, char word[]){
	current=headw;
	
	while(current!=NULL){
		if(!strcmp(current->word,word)){
			return 1;
		}

		current=current->next;
	}
	return 0;

}

// increse word count in the list considering each word frequantly
int increse_Word_count(nodew * head, char word[]){
	current=headw;
	while(current!=NULL){
		if(!strcmp(current->word,word)){
			current->wordCount+=1;
			
			return 1;
		}

		current=current->next;
	}
	return 0;

}

//process the word with only contain Alphebatic and number
char *  Process_Word(char word[],char * word_processed){
	int j=0;
	int i;
	for(i=0;word[i]!='\0';i++){
		if(isalpha(word[i])||isdigit(word[i])){
			*(word_processed+j)=tolower(word[i]);
			j++;
		}
	}
	return word_processed;
}


char  Process_char(char tmpchar){
	if(isalpha(tmpchar)||isdigit(tmpchar)){
		tmpchar=tolower(tmpchar);
		
	}
	return tmpchar;

}

//++++++ command argument inputs check++++++++

//count the -w part in the command arguments

int count_w(char ** argv,int argc){

	int count=0;
	int i=0;

	while(i<argc){
		if(!strcmp("-w",argv[i])){
			count++;
		}
		i++;
	}
	return count;
}

//count the -l part in the command arguments	

int count_l(char ** argv,int argc){
	int count=0;
	int i=0;

	while(i<argc){
		if(!strcmp("-l",argv[i])){
			count++;
		}
		i++;
	}
	return count;

}

//count the -c part in the command arguments

int count_c(char ** argv,int argc){
	int count=0;
	int i=0;

	while(i<argc){
		if(!strcmp("-c",argv[i])){
			count++;
		}
		i++;
	}
	return count;
}

//for count -Scaled  part in argument part 
int count_scaled(char ** argv,int argc){
	int count=0;
	int i=0;

	while(i<argc){
		if(!strcmp("--scaled",argv[i])){
			count++;
		}
		i++;
	}
	return count;
}

//count the readable File name in the command arguments

int readable_File_counter(char ** argv,int argc){
	int i=0;
	int count=0;
	while(i<argc){
		if(fopen(argv[i],"r")){
			count++;;
		}
		i++;
	}
	return count;
}

int Find_length_INDEX(char ** argv,int argc){
	
	int i=0;

	while(i<argc){
		if((!strcmp("-l",argv[i]))&(i < argc-1)){
			return ++i;
		}
		i++;
	}
	return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//----------------------Graph Function-----------------------------

//word Graph+++++++

void print_word_GRAPH(nodew * head , int length,int Scaled_count){

	//find legth list & maximum word length------------
	int list_length=1;
	int max_Word_len=0;
	float max_precentage=0;

	current=head;
	while(current!=NULL){
		list_length++;
		if(max_Word_len<(current->wordLength)){
			max_Word_len=(current->wordLength);
		}
		if(max_precentage<(current->precentage)){
			max_precentage=(current->precentage);
		}

		current=current->next;
	}
	if(list_length<=length){
		int max_count=MaxCountList(headw);
		while(max_count>0){
			current=headw;
			while(current!=NULL){
				if(current->wordCount==max_count){
					print_Bar(max_Word_len,strlen(current->word),current->precentage,current->word,max_precentage,Scaled_count);
				}
				current=current->next;
			}
			max_count--;		
		}
	}

	else{
		int max_count=MaxCountList(headw);
		int n=0;
		int break_count=0;
		max_Word_len=MaxWordLengthCnsdrLength(headw,length);

		while(max_count>0){

			current=headw;

			if(!(break_count<length)){
				break;
			}

			while(current!=NULL){

				if(!(break_count<length)){
					break;
				}
				if(current->wordCount==max_count){

					print_Bar(max_Word_len,strlen(current->word),current->precentage,current->word,max_precentage,Scaled_count);					
					break_count++;
				}
				current=current->next;
			}

			max_count--;
		}
	}

		//end line
		print_Spacing("",max_Word_len,2);

		int i=0;
		while(i<80-3-max_Word_len){
			printf("\u2500");
			i++;
		}

		printf("\n");
}

void print_Bar(int Max_Word_len,int Word_len,float precentage,char word[],float max_precentage,int Scaled_count){
		print_Spacing("",Max_Word_len,1);
	//****
		int e=0;
		int m;
		if(precentage==100){
			m=7;
		}
		else if(precentage<100){
			m=6;
		}
		else if(precentage<10){
			m=5;
		}
		int Bar_len;

		if(Scaled_count>0){
			Bar_len=((precentage/max_precentage)*(80-3-m-Max_Word_len));
		}
		else{
			Bar_len=((precentage/100)*(80-3-m-Max_Word_len));	
		}
		
		

		while(e<Bar_len){
			printf("\u2591");
			e++;
		}
		//****

		printf("\n");
		print_Spacing(word,Max_Word_len,1);
	//****
		e=0;
		while(e<Bar_len){
			printf("\u2591");
			e++;
		}
	//****	

		printf("%.2f%%",precentage );
		printf("\n");
		print_Spacing("",Max_Word_len,1);
	//****
		e=0;
		while(e<Bar_len){
			printf("\u2591");
			e++;
		}
	//****

		printf("\n");

		print_Spacing("",Max_Word_len,1);
		printf("\n");
		
}
void print_Spacing(char word[],int max_Word_len,int s){
	int k=0;
	int wordLength=strlen(word);
	printf(" %s",word);
	while(k<(max_Word_len-wordLength +1)){
		printf(" ");
		k++;
	}
	if(s==1){
		printf("\u2502");
	}
	else{
		printf("\u2514");
	}


}
//++++++++

//char Graph++++++

void print_char_GRAPH(nodec * headc , int length,int Scaled){
	float max_precentage=0;
	currentc=headc;
	while(currentc!=NULL){
		if(max_precentage<(currentc->precentage)){
			max_precentage=(currentc->precentage);
		}

		currentc=currentc->next;
	}

	//find legth list & maximum word length------------
	int list_length=MaxcharCountList(headc);
	int max_char_len=1;
	
	if(list_length<=length){
		int max_count=MaxcharCountList(headc);
		while(max_count>0){
			currentc=headc;
			while(currentc!=NULL){
				if(currentc->charCount==max_count){
					print_char_Bar(1,1,currentc->precentage,currentc->c,max_precentage,Scaled);
				}
				currentc=currentc->next;
			}
			max_count--;		
		}
	}
	else{
		int max_count=MaxcharCountList(headc);
		
		int break_count=0;

		while(max_count>0){

			currentc=headc;

			if(!(break_count<length)){
				break;
			}

			while(currentc!=NULL){

				if(!(break_count<length)){
					break;
				}
				if(currentc->charCount==max_count){
					print_char_Bar(1,1,currentc->precentage,currentc->c,max_precentage,Scaled);					
					break_count++;
				}
				currentc=currentc->next;
			}

			max_count--;
		}
	}

		//end line
		print_Spacing("",1,2);

		int i=0;
		while(i<80-3-1){
			printf("\u2500");
			i++;
		}

		printf("\n");
}

void print_char_Bar(int Max_Word_len,int Word_len,float precentage,char c ,float max_precentage,int Scaled){
			
		print_char_Spacing(' ',1);
	
		int e=0;
		int m;//word length
		if(precentage==100){
			m=7;
		}
		else if(precentage<100){
			m=6;
		}
		else if(precentage<10){
			m=5;
		}

		int Bar_len=0;
		if(Scaled>0){
			Bar_len=(precentage/max_precentage)*(80-3-m-Max_Word_len);
		}
		else{
			Bar_len=(precentage/100)*(80-3-m-Max_Word_len);
		}

		while(e<Bar_len){
			printf("\u2591");
			e++;
		}
		//****

		printf("\n");
		print_char_Spacing(c,1);
	//****
		e=0;
		while(e<Bar_len){
			printf("\u2591");
			e++;
		}
	//****	

		printf("%.2f%%",precentage );
		printf("\n");
		print_char_Spacing(' ',1);
	//****
		e=0;
		while(e<Bar_len){
			printf("\u2591");
			e++;
		}
	//****

		printf("\n");

		print_char_Spacing(' ',1);;
		printf("\n");
		
   }

void print_char_Spacing(char c,int s){
	printf(" %c ",c);
	if(s==1){
		printf("\u2502");
	}
	else{
		printf("\u2514");
	}


}

int MaxcharCountList(nodec * head){
	currentc=head;
	int max_Value=0;
	while(currentc!=NULL){
		if(max_Value<currentc->charCount){
			max_Value=currentc->charCount;	
		}
		currentc=currentc->next;
	}
	return max_Value;

}

int MaxCountList(nodew * head){
	current=head;
	int max_Value=0;
	while(current!=NULL){
		if(max_Value<current->wordCount){
			max_Value=current->wordCount;	
		}
		current=current->next;
	}
	return max_Value;

}

int MaxWordLengthCnsdrLength(nodew * head,int length){ //this  function must use only for list count > length
	current=head;
	int index=length;

	int max_Value=0;
	int consider_length_max_word_length=0;

	while(current!=NULL){
		if(max_Value<current->wordCount){
			max_Value=current->wordCount;	
		}
		current=current->next;
	}

	
	while(index>0){
		current=headw;
		while(current!=NULL){
			if(index<1){
				break;
			}

			if(max_Value==current->wordCount){
				if(consider_length_max_word_length<=current->wordLength){
						consider_length_max_word_length=current->wordLength;
				}
				
				index--;	
			}
			
			current=current->next;
		}
		max_Value--;
	}
	return consider_length_max_word_length;
	

}
