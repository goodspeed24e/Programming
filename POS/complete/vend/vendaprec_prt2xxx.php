<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body onLoad="window.print()">
<?php
// -------------取出所有進貨單的資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT transaction.* FROM transaction WHERE (trandate >='$trandate1' and trandate<='$trandate2' and tranvendno='$tranvendno') ";	
	$res = mysql_query($SQLStr);
	
//--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!---列印完成回首頁 ------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="596" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td width="619"  align="left">
<?php
//--------------頁數選擇呈現及連接---------------
     echo "廠商應付帳款表&nbsp;&nbsp; 第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
	    echo "廠商編號:".$outicustno." ";
		echo "  <a href=index.php?Select=248&page=$i>$i</a>|";
	}
       echo "頁, 共".$total."筆&nbsp;&nbsp";
?> 
    </td>
    </tr>
  </table>
  <table width="595" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="691"> 
        <table width="593" border="0" align="center" >
		  <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>    
          <tr> 
		     <td width="63" align="left" ><font size="-1">  
              進貨日期</font>
            </td>                     
            <td width="71" align="left" ><font size="-1">  
             進貨單號</font> 
            </td>
            <td width="90" align="left" ><font size="-1"> 
			產品編號</font> 
            </td>           
            <td width="123" align="left" ><font size="-1"> 
			產品名稱</font>  
            </td>			
			<td width="54" align="left" ><font size="-1"> 
			數量</font> 
            </td> 
			 <td width="75" align="left" ><font size="-1"> 
			 單價</font> 
            </td>  
			 <td width="87" align="left" ><font size="-1">  
              金額</font></td>    
          </tr>
		  <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>   		  
	<?php
	
//--------------選擇頁數進貨單資料呈現及連接修改頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from transaction WHERE (trandate >='$trandate1' and trandate<='$trandate2' and tranvendno='$tranvendno' ) limit $first , 10";
	  $res = mysql_query($SQLStr);
	  while (list($trancode, $trandate, $tranno, $tranpono, $tranremark, $tranvendno, $tranprodno, $tranprodname, $tranprodqty, $tranunit, $tranpric, $tranamt)=mysql_fetch_row($res))
		{		
//--------------- 取資料表中資料呈現---------------
            echo "<tr border='0'   >";	
			echo "<td align='left'><font size='-1'>" . $trandate . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranno . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranprodno  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranprodname . "</font></td>\n";
			echo "<td align=left''><font size='-1'>" . $tranprodqty . "</font></td>\n";			
			echo "<td align='left'><font size='-1'>" . $tranpric . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranamt . "</font></td>\n";
			echo "</tr>";		  	
		}	
?>   
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>
