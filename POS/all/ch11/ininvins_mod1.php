<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php 
// -------------取出所有進貨單的資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM transaction";
	$res = mysql_query($SQLStr);
//--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>

<form name="form1" method="post" action="ininv/ininvins_mod2.php">

  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
		 <?php
//--------------頁數選擇呈現及連接---------------
     echo "修改進貨單資料&nbsp;&nbsp; 第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=362&page=$i>$i</a>|";
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
             進貨單號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             產品編號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              採購單號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              進貨日期
            </td>             
          </tr>		  
	<?php
//--------------選擇頁數進貨單資料呈現及連接修改頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from transaction order by tranpono limit $first , 10";
	  $res = mysql_query($SQLStr);	
       while (list($trancode, $trandate, $tranno, $tranpono, $tranremark, $tranvendno, $tranprodno, $tranprodname, $tranprodqty, $tranunit, $tranpric, $tranamt)=mysql_fetch_row($res))
		{
//---------------- 抓取進貨資料表中資料並呈現--------------------
            echo "<tr border='0'   bgcolor='#ffffff'>";	
			echo "<td align='center'>" . $tranno  . "</td>\n";
			echo "<td align='center'><a href='ininv/ininvins_mod2.php?tranprodno=" . $tranprodno . "&tranpono=" . $tranpono . "&tranno=" . $tranno . "'>" . $tranprodno . "</a></td>\n";
			echo "<td align='center'>";
			if ($tranpono == '') 
		         $tranpono="無產品編號";	        
			echo  $tranpono . "</td>\n";
			echo "<td align='center'>" . $trandate . "</td>\n";	
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
	
