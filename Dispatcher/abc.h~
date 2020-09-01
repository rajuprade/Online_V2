void* highuser( void* parameters)
{
   int flag;
   command c1;
   while((name=readline("\n >> "))!=NULL)
    {
      if (strcmp(name,"stop")==0)
      continue;
      printf("\n");
      if(name)
      {
        strcpy(c1.system_name,name);
        q_store(c1);
      }
       
      usleep(10000);
       if (name[0]!=0)
            add_history(name);
     }
   free(name);
   return NULL;
}
