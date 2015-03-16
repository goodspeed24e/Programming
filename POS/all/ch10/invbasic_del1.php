<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php
// -------------取出所有產品的資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM product";
	$res = mysql_query($SQLStr);
//--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!--執行產品基本資料選擇後,進入invbasic_del2.php連接網頁呈現------->
<form name="form1" method="post" action="inv/invbasic_del2.php">
  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
	  	  <?php
//--------------頁數選擇呈現及連接---------------
     echo "刪除產品資料&nbsp;&nbsp; 第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=304&page=$i>$i</a>|";
	}
       echo "頁, 共".$total."筆&nbsp;&nbsp";
?>
   </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="1" align="center" bgcolor="#FFFFFF" >
          <tr> 
		   <td bgcolor="#99CCFF" align="center"> 
             產品編號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             產品名稱
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              規格說明
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              供應廠商
            </td> 
          </tr>
		  
<?php
//--------------選擇頁數產品資料呈現及連接刪除頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from product order by prodno  limit $first , 10";
	  $res = mysql_query($SQLStr);	
 while (list($prodno, $prodname, $prodtype, $prodvend, $produnit, $prodipric, $prodspric, $prodsave, $prodpqty, $prodnqty, $prodgrap, $prodsdesp, $proddesp, $prodidate, $prododate)=mysql_fetch_row($res))
  {
//-------------------------- 抓取資料表中其他資料並呈現----------------------------------
            echo "<tr border='0'   bgcolor='#ffffff'>";	
			echo "<td align='center'>" . $prodno  . "</td>\n";
			echo "<td align='center'><a href='inv/invbasic_del2.php?prodno=" . $prodno . "'>" . $prodname . "</a></td>\n";
			echo "<td align='center'>";
			if ($prodsdesp == '') 
		         $prodsdesp="無規格說明";	        
			echo  $prodsdesp . "</td>\n";			
			echo "<td align='center'>" . $prodvend . "</td>\n";	
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