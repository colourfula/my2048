  1 #include<stdio.h>
  2 #include<stdlib.h>
  3 #include<curses.h>
  4 #include<time.h>
  5 #include<unistd.h>
  6 #include<signal.h>
  7 
  8 
  9 void draw_one(int y,int x);
 10 void cnt_value(int *new_y,int *new_x);
 11 
 12 int a[4][4]={0};
 13 int empty;
 14 int old_y;
 15 int old_x;
 16 
 17 void draw()
 18 {
 19   int m,n,x,y;
 20   char c[4] = {'0','0','0','0'};
 21 
 22   clear();
 23   for(n=0;n<9;n+=2)
 24 
 25      for(m=0;m<21;m++){
 26         move(n,m);
 27         addch('-');
 28         refresh();
 29   }
 30 
 31  for(m=0;m<22;m+=5)
 32    for(n=1;n<8;n++){
 33         move(n,m);
 34         addch('|');
 35         refresh();
 36   }
 37   for(y=0;y<4;y++)
 38    for(x=0;x<4;x++){
 39        draw_one(y,x);
 40   }
 41 }
 42 
 43 void play()
 44 {
 45   int x,y,i,new_x,new_y,temp;
 46   int old_empty,move;
 47   char ch;
 48 
 49   while(1){
 50     move=0;
 51     old_empty=empty;
 52     ch=getch();
 53     switch(ch)
 54      {
 55       case 97:
 56       case 104:
 57       case 68:
 58         for(y=0;y<4;y++)
 59           for(x=0;x<4;)
 60             {
 61              if(a[y][x]==0)
 62               {
 63                x++;
 64                continue;
 65               }
 66              else
 67               {
 68                  for(i=x+1;i<4;i++)
 69                   {
 70                     if(a[y][i]==0)
 71                     {
 72                       continue;
 73                     }
 74                     else
 75                     {
 76                       if(a[y][x]==a[y][i])
 77                         {
 78                            a[y][x]+=a[y][i];
 79                            a[y][i]=0;
 80                            empty++;
 81                            break;
 82                         }
 83                        else
 84                         {
 85                            break;
 86                         }
 87                      }
 88                   }
 89                    x=i;
 90               }
 91            }
 92      for(y=0;y<4;y++)
 93        for(x=0;x<4;x++)
 94          {
 95          if(a[y][x]==0)
 96            {
 97              continue;
 98            }
 99           else
100            {
101              for(i=x;(i>0)&&(a[y][i-1]==0);i--)
102                 {
103                   a[y][i-1]=a[y][i];
104                   a[y][i]=0;
105                   move=1;
106                 }
107            }
108          }
109        break;
110     case  100:
111     case 108:
112     case 67:
113       for(y=0;y<4;y++)
114         for(x=3;x>=0;)
115           {
116           if(a[y][x]==0)
117             {
118               x--;
119               continue;
120             }
121            else
122             {
123               for(i=x-1;i>=0;i--)
124                 {
125                   if(a[y][i]==0)
126                     {
127                       continue;
128                     }
129                   else if(a[y][x]==a[y][i])
130                     {
131                        a[y][x]+=a[y][i];
132                        a[y][i]=0;
133                        empty++;
134                        break;
135                     }
136                  else
137                     {
138                        break;
139                     }
140                 }
141                   x=i;
142              }
143          }
144         for(y=0;y<4;y++)
145         for(x=3;x>=0;x--)
146           {
147             if(a[y][x]==0)
148               {
149                 continue;
150               }
151              else{
152                 for(i=x;(i<3)&&(a[y][i+1]==0);i++)
153                    {
154                      a[y][i+1]=a[y][i];
155                      a[y][i]=0;
156                      move=1;
157                    }
158                  }
159           }
160         break;
161     case 119:
162     case 107:
163     case 65:
164       for(x=0;x<4;x++)
165         for(y=0;y<4;)
166           {
167             if(a[y][x]==0)
168               {
169                 y++;
170                 continue;
171               } 
172             else
173               {
174                 for(i=y+1;i<4;i++)
175                   {
176                     if(a[i][x]==0)
177                       {
178                         continue;
179                       }
180                     else if(a[y][x]==a[i][x])
181                       {
182                          a[y][x]+=a[i][x];
183                          a[i][x]=0;
184                          empty++;
185                          break;
186                       }
187                    else
188                       {
189                           break;
190                       }
191                  }
192                y=i;
193              }
194           }
195          for(x=0;x<4;x++)
196          for(y=0;y<4;y++)
197            {
198              if(a[y][x]==0)
199                {
200                  continue;
201                }
202              else
203                {
204                  for(i=y;(i>0)&&(a[i-1][x]==0);i--)
205                    {
206                      a[i-1][x]=a[i][x];
207                      a[i][x]=0;
208                      move=1;
209                    }
210                }
211             }
212          break;
213    case 115://s
214    case 106://j
215    case 66://down
216      for(x=0;x<4;x++)
217        for(y=3;y>=0;)
218          {
219          if(a[y][x]==0)
                                                                 220            {
221              y--;
222              continue;
223            }
224          else
225            {
226              for(i=y-1;i>=0;i--)
227                {
228                  if(a[i][x]==0)
229                    {
230                      continue;
231                    }
232                  else if(a[y][x]==a[i][x])
233                    {
234                       a[y][x]+=a[i][x];
235                       a[i][x]=0;
236                       empty++;
237                       break;
238                    }
239                  else
240                    {
241                      break;
242                    }
243                }
244             y=i;
245            }
246         }
247           for(x=0;x<4;x++)
248              for(y=3;y>=0;y--)
249                {
250                   if(a[y][x]==0)
251                     {
252                       continue;
253                     }
254                   else
255                     {
256                       for(i=y;(i<3)&&(a[i+1][x]==0);i++)
257                         {
258                            a[i+1][x]=a[i][x];
259                            a[i][x]=0;
260                            move=1;
261                         }
262                     }
263                }
264             break;
265      case 'Q':
266      case 'q':
267        game_over();
268        break;
269      default:
270        continue;
271        break;
272     }
273    if(empty <= 0)
274      game_over();
275    if((empty != old_empty) || (move==1)){
276      do{
277        new_x = rand()%4;
278        new_y = rand()%4;
279       }while(a[new_y][new_x] != 0);
280      cnt_value(&new_y,&new_x);
281      do{
282         temp=rand()%4;
283       }while(temp==0 || temp==2);
284        a[new_y][new_x]=temp+1;
285        empty--;
286     }
287    draw();
288   }
289 }
290 
291 void init()
292 {
293   int x,y;
294 
295   initscr();
296   cbreak();
297   noecho();
298   curs_set(0);
299 
300   empty=15;
301   srand(time(0));
302   x=rand()%4;
303   y=rand()%4;
304   a[y][x]=2;
305   draw();
306 }
307 
308 
309 void draw_one(int y,int x)
310 {
311   int i,m,k,j;
312   char c[5]={0x00};
313   i=a[y][x];
314   m=0;
315   while(i>0){
316     j=i%10;
317     c[m++]=j+'0';
318     i=i/10;
319   }
320  m=0;
321  k=(x+1)*5-1;
322  while(c[m]!=0x00){
323     move(2*y+1,k);
324     addch(c[m++]);
325     k--;
326   }
327 }
328 
329 void cnt_value(int *new_y,int *new_x)
330 {
331   int max_x,max_y,x,y,value;
332   int max=0;
333 
334   max=cnt_one(*new_y,*new_x);
335   for(y=0;y<4;y++)
336     for(x=0;x<4;x++){
337       if(! a[y][x]){
338         value=cnt_one(y,x);
339         if(value > max && old_y != y && old_x != x){
340           *new_y = y;
341           *new_x = x;
342           old_x = x;
343           old_y = y;
344           break;
345       }
346     }
347   }
348 }
349 
350 
351 int game_over()
352 {
353   sleep(1);
354   endwin();
355   exit(0);
356 }
357 
358 
359 int cnt_one(int x,int y)
360 {
361   int value=0;
362   if(y-1>0)
363     a[y-1][x] ? 0 : value++;
364   if(y+1<4)
365     a[y+1][x] ? 0 : value++;
366 
367   if(x-1>0)
368     a[y][x-1] ? 0 : value++;
369   if(x+1<4)
370     a[y][x+1] ? 0 : value++;
371 
372 
373   if(y-1>=0 && x-1>=0)
374     a[y-1][x-1] ? 0 : value++;
375   if(y-1>=0 && x+1<4)
376     a[y-1][x+1] ? 0 : value++;
377 
378   if(y+1<4 && x-1>=0)
379     a[y+1][x-1] ? 0 : value++;
380   if(y+1<4 && x+1<4)
381     a[y+1][x+1] ? 0 : value++;
382 
383   return value;
384 }
385 
386 int main()
387 {
388   init();
389   play();
390   endwin();
391   return 0;
392 }
