1、获取信息 done 

2、对信息顺序进行重排 awk '{print $9,$3,$1}' output.txt  done

3、管道到新的output.txt done

3、每行加入b  xargs  todo

4、排序  sort