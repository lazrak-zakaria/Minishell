

Play with 
{
	echo "$'USER'" 
	echo "$'USER'"
	Etc
}


/********  here_doc  **********/

observe Who's expands and who's not !

<< $USER cat 

<< "$USER" cat 

<< $"USER" cat

<< '$USER' cat

<< "limit" cat

<< limit cat

With this input :

> ----
> $?
> any env variable
> ----

Test ex :

<< $"" cat
<< ""$ cat
<< $'' cat
<< ''$ cat
<< $U'SER' cat



/********************************/

export JJ="    T E      S T"

What's the output?

-----> echo $JJ
-----> cat $JJ
-----> echo hi > $JJ
-----> export

Any difference?


/*******************************/


