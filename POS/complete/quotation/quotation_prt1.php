<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body >
<?php 
    // -------------取出所有報價資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM  quotationwork";
	$res = mysql_query($SQLStr);
	
    //--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!------傳給quotation_prt2.php,執行列印---->
<form name="form1" method="post" action="quotation/quotation_prt2.php?quwkno=' . $quwkno . '">
  <table width="782" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
		 <?php
    //--------------頁數選擇呈現及連接---------------
     echo "列印報價單資料&nbsp;&nbsp; 第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=180&page=$i>$i</a>|";
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
             報價單號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             客戶
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              交貨日期
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              銷售類別
            </td>             
          </tr>		  
	<?php
      //--------------選擇頁數報價單資料呈現及連接頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from quotationwork order by quwkno limit $first , 10";
	  $res = mysql_query($SQLStr);	 
        while (list($quwkno, $quwkprod, $quwkcust, $quwktype, $quwkpric, $quwkqty, $quwksqty, $quwksdate, $quwkunit, $quwkprodname, $quwkcustname)=mysql_fetch_row($res))
		{
        //-------------- 抓取報價單資料表中資料並呈現-----------------
            echo "<tr border='0'   bgcolor='#ffffff'>";			
			echo "<td align='center'><a href='quotation/quotation_prt2.php?quwkno=" . $quwkno . "&quwkprodno=".$quwkprodno ."&quwkcust=".$quwkcust."&quwkcustname=".$quwkcustname."&quwktype=".$quwktype."&quwksdate=".$quwksdate."'>" . $quwkno . "</a></td>\n";
			echo "<td align='center'>" . $quwkcust  ."/" . $quwkcustname . "</td>\n";
			echo "<td align='center'>";
			   if ($quwksdate == '') 
			      $quwksdate="無交期";	        
			      echo  $quwksdate . "</td>\n";
            echo "<td align='center'>";			  
			   if ($quwktype == '') 
			      $quwktype="照慣例";	        
			      echo  $quwktype . "</td>\n";
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
