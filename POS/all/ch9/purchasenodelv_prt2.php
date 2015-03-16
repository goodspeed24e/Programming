<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body >
<?php 
    // -------------取出所有已訂未交資料---------------
	include("mysqlcntdb.php");
	$dt=date("Y-m-d");		
	$SQLStr = "SELECT purchase.*  FROM purchase WHERE ( purchprodqty > purchinqty and purchtranno = $purchtranno)";	
	$res = mysql_query($SQLStr);
    //--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!----傳給purchasenodelv_prt2.php,執行列印   ---->
<form name="form1" method="post" action="purchase/purchasenodelv_prt2.php?purchtranno=' . $purcmtranno . '">
  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
<?php
    //--------------頁數選擇呈現及連接---------------
     echo "已訂未交貨採購資料&nbsp;&nbsp; 第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=290&page=$i>$i</a>|";
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
             產品編號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             供應廠商
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              交貨日期
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              採購單號			  
            </td> 
			 <td bgcolor="#99CCFF" align="center"> 
              訂購數量			  
            </td>  
			 <td bgcolor="#99CCFF" align="center"> 
              未交數量			  
            </td>   
			            
          </tr>		  
	<?php
//--------------選擇頁數,取出所有已訂未交資料呈現及連接頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);	  
	  $SQLStr = "SELECT *  FROM purchase  WHERE ( purchprodqty > purchinqty and purchtranno = $purchtranno)";	
	  $res = mysql_query($SQLStr);
       while (list($purchtranno, $purchprodno,  $purchprodqty, $purchinqty, $purchpric)=mysql_fetch_row($res))
		{
		//------------ 抓取資料表中,已訂未交資料呈現----------------
            echo "<tr border='0'   bgcolor='#ffffff'>";				
			echo "<td align='center'>" . $purchprodno . "</td>\n";
			echo "<td align='center'>" . $purcmvend . "</td>\n";
			echo "<td align='center'>";
			   if ($purcmdate == '') 
			      $purcmdate="無交期";	        
			      echo  $purcmdate . "</td>\n";
            echo "<td align='center'>" . $purchtranno . "</td>\n";	
			echo "<td align='center'>" . $purchprodqty  . "</td>\n";	
			$qty= $purchprodqty - $purchinqty;
			echo "<td align='center'>" . $qty  . "</td>\n";						
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
