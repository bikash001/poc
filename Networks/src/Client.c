/*-------------------------------------------------------------------------
 *  Client.c - Client Program for sending messages to the server
 *  Version:	$Name:  $
 *  Module:	
 *
 *  Purpose:	
 *  See:	
 *
 *  Author:	Hema Murthy (hema@bhairavi.iitm.ernet.in)
 *
 *  Created:        Sat 17-Mar-2007 14:09:41
 *  Last modified:  Mon 26-Mar-2007 09:54:20 by hema
 *  $Id: Client.c,v 1.1 2007/03/26 04:26:09 hema Exp hema $
 *
 *  Bugs:	
 *
 *  Change Log:	<Date> <Author>
 *  		<Changes>
 -------------------------------------------------------------------------*/

/* 
 * Example of client using UDP protocol.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "strings.h"
#include "string.h"
#include "include/DgFunctions.h"
#include <time.h>

//int error; //index of error bit
int count=0;	//total count after last error
//packet size of 56bit, each packet of 7bit
void gen_error(char *msg,double errorp)
{
	//char str[8];
	char byte;
	int j=3,i=3;
	//int temp;
	char eb;
	double p=0.0;
	for(j=0; j<7; ++j){
		byte = msg[j];
		for(i=0; i<8; i++){
			p = ((double)rand())/RAND_MAX;
			if(p < errorp){
				count++;
				eb = 0x1;
				eb = eb << i;
				byte = byte ^ eb;
			}
		}
		msg[j] = byte;
	}
	/*for(j=0; j<7; ++j){
		if(count+7 > error){
			temp = 7 - (error-count);
			eb = 0x1;
			eb = eb << temp;
			byte = msg[j];
			byte = byte ^ eb;
			str[j] = byte;
			count = temp;
		}else{
			str[j] = msg[j];
			count += 7;
		}
	}
	str[7]='\0';
	strncpy(msg,str,8);*/
}


/*-------------------------------------------------------------------------
 *  Usage -- Prints the usage for the program
 *    Args:	
 *    Returns:	Nothing
 *    Throws:	
 *    See:	
 *    Bugs:	
 -------------------------------------------------------------------------*/
void Usage () {
  printf ("Client ServerIPAddr ServerPort ClientIPAddress ClientPort\n");
}


/*-------------------------------------------------------------------------
 *  main -- Main Program for the Client - sends 10 lines of text to server
 *    Args:	Takes as arguments ServerIP, ServerPort, ClientIP, ClientPort
 *    Returns:	Nothing
 *    Throws:	
 *    See:	Unix Network Programming: Richard Stevens - Vol I
 *    Bugs:	
 -------------------------------------------------------------------------*/
int  main (int argc, char **argv)
{
//	srand(10);
	int                   sockFd;
	int                   serverPortNumber, clientPortNumber;
	struct sockaddr_in    clientAddr,serverAddr;
	//char                  *sendMsg = "Testing UDP Protocol\n";
	char	sendMsg[8]; //packet size

	FILE* fp = fopen("input", "rb");  //input data after channel coding

	//bit error rate
	double ber = 0.001; //error probability
	//error = (int)(1/ber);

	if (argc != 5) {
	  Usage();
	  exit(-1);
	}
	
	 /* Fill in the structure "serverAddr " with the address of the 
	 * server that we want to send to .
	 */
	sscanf(argv[2],"%d", &serverPortNumber); 
	sscanf(argv[4],"%d", &clientPortNumber); 

	bzero(( char *) &serverAddr , sizeof (serverAddr));
	serverAddr.sin_family   = AF_INET;
	serverAddr.sin_addr.s_addr =inet_addr(argv[1]);
	serverAddr.sin_port  = htons(serverPortNumber);
  
  
	/* 
	 * Open a UDP socket (an Internet datagram socket).
	 */
	 
	if (( sockFd = socket(AF_INET,SOCK_DGRAM ,0)) < 0) {
	  	printf("client : can't open datagram socket \n");
	  	exit(-1);
	}
	/* 
	 * Bind any local address for us.
	 */
	
	printf ("Socket bound\n");    

	
	bzero(( char *) &clientAddr , sizeof (clientAddr));
	clientAddr.sin_family   = AF_INET;
	clientAddr.sin_addr.s_addr =inet_addr(argv[3]);
	clientAddr.sin_port  = htons(clientPortNumber);
  
	if (bind (sockFd, (struct sockaddr *) &clientAddr ,sizeof(clientAddr)) < 0) {
	  	printf(" client: can't bind  local address\n");
	  	exit(-1);
	}
   
	int j;
	int k=0;
//	for(j=0; j<100; j++,k++){
	while(!feof(fp)){
		k++;
		if(fread(sendMsg,1,7,fp)<7){
		  	printf("size zero\n");
		  	break;
		}
		sendMsg[7] = '\0';
		//printf ("Message sent = %s\n", sendMsg);
	
		gen_error(sendMsg,ber);  //channel noise
		if(!DgClient(sendMsg, sockFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr))){
			fseek(fp,-7,SEEK_CUR);
			j--;
		}
	}
	printf("success %d, %d\n",k,count);
	fclose(fp);
	close(sockFd);
	exit(0);
	return(0);
}	/*  End of main		End of main   */
	  


/*-------------------------------------------------------------------------
 * $Log: Client.c,v $
 * Revision 1.1  2007/03/26 04:26:09  hema
 * Initial revision
 *
 *
 * Local Variables:
 * time-stamp-active: t
 * time-stamp-line-limit: 20
 * time-stamp-start: "Last modified:[ 	]+"
 * time-stamp-format: "%3a %02d-%3b-%:y %02H:%02M:%02S by %u"
 * time-stamp-end: "$"
 * End:
 *                        End of Client.c
 -------------------------------------------------------------------------*/
