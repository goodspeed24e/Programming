<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body onLoad="window.print()">
<?php
// -------------取出所有進貨單的資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT transaction.* FROM transaction WHERE (tranprodno >='$tranprodno1' and tranprodno<='$tranprodno2') ";	
	$res = mysql_query($SQLStr);
	
//--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/30);
?>
<!----執行列印完成,回主目錄------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="599" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td width="691" align="left">
		 <?php
//--------------頁數選擇呈現及連接---------------
     echo "進貨紀錄簿&nbsp;&nbsp;<br><font size='-1'>產品編號".$tranprodno1."至".$tranprodno2. " 第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=380&page=$i>$i</a>|";
	}
       echo "頁, 共".$total."筆&nbsp;&nbsp</font>";
?>   
	  
    </td>
    </tr>
  </table>
  <table width="601" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="782"> 
        <table width="598" border="0" align="center" >
		    <tr> 
            <td  align="left" colspan="8"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>	 
          <tr> 
		     <td width="64"  align="left"><font size="-1"> 
              產品編號</font>
            </td>                     
            <td width="87"  align="left"><font size="-1"> 
             產品名稱</font>
            </td>
            <td width="73"  align="left"><font size="-1"> 
             採購單號</font>
            </td>           
            <td width="59"  align="left"><font size="-1"> 
              進貨日期</font>
            </td>			
			<td width="84"  align="left"><font size="-1"> 
             進貨單號</font> 
            </td> 
			 <td width="65"  align="left"><font size="-1"> 
              廠商</font>
            </td>  
			 <td width="58"  align="left"><font size="-1"> 
              單價</font>
            </td>      
			 <td width="74"  align="left"><font size="-1"> 
              進貨數</font>
            </td>                  
          </tr>
		    <tr> 
            <td  align="left" colspan="8"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>	 		  
	<?php
//--------------選擇頁數進貨單資料呈現及連接頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=30*($page - 1);
	  $SQLStr="select * from transaction WHERE (tranprodno >='$tranprodno1' and tranprodno<='$tranprodno2') limit $first , 30";
	  $res = mysql_query($SQLStr);	 
       while (list( $trancode,$trandate,$tranno,$tranpono,$tranremark,$tranvendno,$tranprodno,$tranprodname,$tranprodqty,$tranunit,$tranpric,$tranamt)=mysql_fetch_row($res))
		{
//------------------------- 抓取資料表中資料並呈現進貨紀錄------------------
            echo "<tr border='0' >";	
			echo "<td align='left'><font size='-1'>" . $tranprodno . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranprodname . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranpono  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $trandate  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranno . "</font></td>\n";			
			echo "<td align='left'><font size='-1'>" . $tranvendno . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranpric . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranprodqty . "</font></td>\n";	
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
