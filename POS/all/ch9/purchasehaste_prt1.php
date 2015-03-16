<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php 
    // -------------取出所有採購主資料表逾期未進貨的資料---------------
	include("mysqlcntdb.php");
	$dt=date("Y-m-d");	
	$SQLStr = "SELECT * FROM  purchmst WHERE purcmdate >= '$dt'";
	$res = mysql_query($SQLStr);
    //--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!------傳給purchasehaste_prt2.php,執行搜尋---->
<form name="form1" method="post" action="purchase/purchasehaste_prt2.php?purcmtranno=' . $purcmtranno . '">
  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
<?php
    //--------------頁數選擇呈現及連接---------------
     echo "催貨資料&nbsp;&nbsp; 第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=280&page=$i>$i</a>|";
	}
       echo "頁, 共".$total."筆&nbsp;&nbsp";
?> 
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="1" align="center" bgcolor="#FFFFFF">
          <tr>                     
            <td bgcolor="#99CCFF" align="center"> 
             採購單號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             供應廠商
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              交貨日期
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              採購類別
            </td>             
          </tr>		  
	<?php
      //--------------選擇頁數,採購主資料表逾期未進貨資料呈現及連接頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from purchmst   WHERE purcmdate >= '$dt'  limit $first , 10";
	  $res = mysql_query($SQLStr);	  	
       while (list($purcmtranno, $purcmvend,  $purcmdate, $purcmtype)=mysql_fetch_row($res))
		{
        //--------------- 抓取採購主資料表逾期未進貨資料並呈現-----------------------
            echo "<tr border='0'   bgcolor='#ffffff'>";			
			echo "<td align='center'><a href='purchase/purchasehaste_prt2.php?purchtranno=" . $purcmtranno . "&purcmdate=".$purcmdate."&purcmvend=".$purcmvend."'>" . $purcmtranno . "</a></td>\n";
			echo "<td align='center'>" . $purcmvend  . "</td>\n";
			echo "<td align='center'>";
			   if ($purcmdate == '') 
			      $purcmdate="無交期";	        
			      echo  $purcmdate . "</td>\n";
            echo "<td align='center'>";			  
			   if ($purcmtype == '') 
			      $purcmtype="照慣例";	        
			      echo  $purcmtype . "</td>\n";
			echo "</tr>";		  	
		}	
?>         <tr>                     
            <td bgcolor="#99CCFF" align="center" colspan="4"> 
             <font color="#FF0000">已訂購未超過交期待催貨產品資訊顯示</font>
            </td>                       
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>
