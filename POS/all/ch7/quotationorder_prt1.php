<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php 
    // -------------取出報價單已銷售的資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM  quotationwork WHERE quwksqty  > 0";
	$res = mysql_query($SQLStr);
    //--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!------ 完成搜尋,傳給主目錄------>
<form name="form1" method="post" action="index.php?Select=10">

  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
		 <?php
    //--------------頁數選擇呈現及連接---------------
     echo "客戶訂購資料&nbsp;&nbsp; 第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=160&page=$i>$i</a>|";
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
             估價單號
            </td>
			 <td bgcolor="#99CCFF" align="center"> 
             客戶編號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             產品編號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              估價數量
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              售價
            </td> 
			<td bgcolor="#99CCFF" align="center"> 
              估價日期
            </td>              
          </tr>		  
	<?php
      //--------------選擇頁數報價已銷售資料呈現及連接頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from quotationwork WHERE quwksqty > 0 limit $first , 10";
	  $res = mysql_query($SQLStr);	
       while (list($quwkno, $quwkprod, $quwkcust, $quwktype, $quwkpric, $quwkqty, $quwksqty,$quwksdate)=mysql_fetch_row($res))
		{
		//-------------- 抓取報價已銷售資料表中資料並呈現----------------
            echo "<tr border='0'   bgcolor='#ffffff'>";	
			echo "<td align='center'>" . $quwkno  . "</td>\n";
			echo "<td align='center'>" . $quwkcust  . "</td>\n";
			echo "<td align='center'>" . $quwkprod . "</td>\n";
			echo "<td align='center'>" . $quwkqty . "</td>\n";	
			echo "<td align='center'>" . $quwkpric . "</td>\n";				
			echo "<td align='center'>" . $quwksdate . "</td>\n";	
			echo "</tr>";		  	
		}	
?> 
       <tr>
	   <td colspan="6" align="center"><input name="closewindows"  type="submit"  value="結束"></td>
	   </tr>    
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>
