<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統vendaprec_prt2</title>
</head>
<body onLoad="window.print()">
<?php
// ------------------取出所有進貨單的資料---------------
	include("mysqlcntdb.php");
//------------------- 依搜尋條件取出, 進貨資料內容 ---------------
	$SQLStr = "SELECT transaction.* FROM transaction WHERE (trandate >='$trandate1' and trandate<='$trandate2' and tranvendno='$tranvendno') ";	
	$res = mysql_query($SQLStr);

	
//--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!----執行列印結束,回首頁----------->
<form name="form1" method="post" action="../index.php?Select=10">

  <table width="782" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
		 <?php
//--------------頁數選擇呈現及連接---------------
     echo "廠商應付帳款表&nbsp;&nbsp; 第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
	    echo "廠商編號:".$tranvendno." ";
		echo "  <a href=index.php?Select=248&page=$i>$i</a>|";
	}
       echo "頁, 共".$total."筆&nbsp;&nbsp";
?>   
	  
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="0" align="center" bgcolor="#FFFFFF">
          <tr> 
		     <td width="114" align="center" bgcolor="#99CCFF"> 
              進貨日期
            </td>                     
            <td width="114" align="center" bgcolor="#99CCFF"> 
             進貨單號 
            </td>
            <td width="114" align="center" bgcolor="#99CCFF">產品編號 
            </td>           
            <td width="114" align="center" bgcolor="#99CCFF">產品名稱  
            </td>			
			<td width="63" align="center" bgcolor="#99CCFF">數量 
            </td> 
			 <td width="63" align="center" bgcolor="#99CCFF">單價 
            </td>  
			 <td width="73" align="center" bgcolor="#99CCFF"> 
              金額</td>      
			                  
          </tr>		  
	<?php
//--------------選擇頁數廠商進貨單資料呈現及連接列印頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from transaction WHERE (trandate >='$trandate1' and trandate<='$trandate2' and tranvendno='$tranvendno') limit $first , 10";
	  $res = mysql_query($SQLStr);	
	   while (list($trancode, $trandate, $tranno, $tranpono, $tranremark, $tranvendno, $tranprodno, $tranprodname, $tranprodqty, $tranunit, $tranpric, $tranamt)=mysql_fetch_row($res))
		{
//--------------- 抓取資料表中資料並列印------------------------
            echo "<tr border='0'   bgcolor='#ffffff'>";	
			echo "<td align='center'>" . $trandate . "</td>\n";
			echo "<td align='center'>" . $tranno . "</td>\n";
			echo "<td align='center'>" . $tranprodno  . "</td>\n";
			echo "<td align='center'>" . $tranprodname . "</td>\n";
			echo "<td align='center'>" . $tranprodqty . "</td>\n";			
			echo "<td align='center'>" . $tranpric . "</td>\n";
			echo "<td align='center'>" . $tranamt . "</td>\n";
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
