<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php
// -------------取出所有銷貨單的資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM outinv";
	$res = mysql_query($SQLStr);
//--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>

<form name="form1" method="post" action="outinv/outinvout_mod2.php">

  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
	 <?php
//--------------頁數選擇呈現及連接---------------
     echo "修改銷貨單資料&nbsp;&nbsp; 第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=402&page=$i>$i</a>|";
	}
       echo "頁, 共".$total."筆&nbsp;&nbsp";
?> 
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="1" align="center"  bgcolor="#FFFFFF">
          <tr>                     
            <td bgcolor="#99CCFF" align="center"> 
             銷貨單號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              產品編號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              產品名稱
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              銷貨日期
            </td>             
          </tr>
<?php
//--------------選擇頁數銷貨單資料呈現及連接修改頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from outinv order by outino,outiprodno  limit $first , 10";
	  $res = mysql_query($SQLStr);
	   while (list($outicode, $outino, $outiprodno, $outidate, $outiremark, $outicustno, $outiprodname, $outiprodqty, $outiunit, $outipric, $outiamt)=mysql_fetch_row($res))
		{
//---------------- 抓取銷貨資料表中資料並呈現--------------------
            echo "<tr border='0'   bgcolor='#ffffff'>";	
			echo "<td align='center'>" . $outino  . "</td>\n";
			echo "<td align='center'><a href='outinv/outinvout_mod2.php?outino=" . $outino . "&outiprodno=" . $outiprodno . "'>" . $outiprodno . "</a></td>\n";
			echo "<td align='center'>";
			if ($outiprodname == '') 
		         $outiprodname="無產品名稱";	        
			echo  $outiprodname . "</td>\n";
			echo "<td align='center'>" . $outidate . "</td>\n";			
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
