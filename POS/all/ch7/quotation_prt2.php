<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body  onLoad="window.print()">
<?php 
// -------------取出所有報價單號符合條件的報價單資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM  quotationwork  where quwkno=$quwkno";
	$res = mysql_query($SQLStr);
//--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	
?>
<!------ 完成列印,傳給主目錄------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="598" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td width="598"     align="left"><font size="-1"> 
		 <?php
//--------------頁數選擇呈現及連接---------------
     echo "報價單<br>";
	 echo "報價單號:".$quwkno."&nbsp;&nbsp;客戶:".$quwkcust."/".$quwkcustname."&nbsp;&nbsp;報價類別:".$quwktype."&nbsp;&nbsp;報價日期:".$quwksdate."<br>";
?> 
    </font></td>
    </tr>
  </table>
  <table width="602" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="602"> 
        <table width="596" border="0" align="center" >
		  <tr> 
            <td  align="left" colspan="4"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>
          <tr>                     
            <td  align="left"><font size="-1">  
             產品編號</font>
            </td>
            <td  align="left"><font size="-1">  
              產品名稱</font>
            </td>
            <td  align="left"><font size="-1">  
              報價數量</font>
            </td>
            <td align="left"><font size="-1">  
              單價</font>
            </td>             
          </tr>
		    <tr> 
            <td  align="left" colspan="4"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>		  
	<?php
      //--------------選擇頁數報價單資料呈現及連接頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from quotationwork where quwkno=$quwkno limit $first , 10";
	  $res = mysql_query($SQLStr);
       while (list($quwkno, $quwkprod, $quwkcust, $quwktype, $quwkpric, $quwkqty, $quwksqty, $quwksdate, $quwkunit, $quwkprodname, $quwkcustname)=mysql_fetch_row($res))
		{
        //---------------- 抓取報價單資料表中資料並呈現----------------
            echo "<tr border='0'>";	
			echo "<td align='left'><font size='-1'>" . $quwkprod  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $quwkprodname . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $quwkqty . "</font></td>\n";	
			echo "<td align='left'><font size='-1'>" . $quwkpric . "</font></td>\n";	
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