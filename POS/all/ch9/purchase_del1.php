<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php 
    // -------------取出所有採購明細資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM  purchase";
	$res = mysql_query($SQLStr);
    //--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>

<form name="form1" method="post" action="purchase/purchase_del2.php">
  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
		 <?php
    //--------------頁數選擇呈現及連接---------------
     echo "刪除採購單資料&nbsp;&nbsp; 第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=254&page=$i>$i</a>|";
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
             產品編號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              採購數量
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              單價
            </td>             
          </tr>		  
	<?php
      //--------------選擇頁數採購明細資料呈現及連接頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from purchase order by purchtranno limit $first , 10";
	  $res = mysql_query($SQLStr);	
       while (list($purchtranno, $purchprodno, $purchprodqty, $purchinqty, $purchpric)=mysql_fetch_row($res))
		{
       // ---------------抓取採購明細資料表中資料並呈現------------------------
            echo "<tr border='0'   bgcolor='#ffffff'>";	
			echo "<td align='center'>" . $purchtranno  . "</td>\n";
			echo "<td align='center'><a href='purchase/purchase_del2.php?purchprodno=" . $purchprodno . "&purchtranno=" .$purchtranno. "'>" . $purchprodno . "</a></td>\n";
			echo "<td align='center'>" . $purchprodqty . "</td>\n";	
			echo "<td align='center'>" . $purchpric . "</td>\n";			
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
	
