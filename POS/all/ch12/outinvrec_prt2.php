<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body onLoad="window.print()">
<?php
// -------------取出所有銷貨單的資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT outinv.* FROM outinv WHERE (outiprodno >='$outiprodno1' and outiprodno<='$outiprodno2') ";	
	$res = mysql_query($SQLStr);
	
//--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/30);
?>
<!----執行列印完成,回主目錄------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="598" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td width="653"  align="left">
		 <?php
//--------------頁數選擇呈現及連接---------------
     echo "銷貨紀錄簿&nbsp;&nbsp;<br><font size='-1'>產品編號" .$outiprodno1. "至" .$outiprodno2.  "第&nbsp;";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=420&page=$i>$i</a>|";
	}
       echo "頁, 共".$total."筆&nbsp;&nbsp</font>";
?>   
	  
    </td>
    </tr>
  </table>
  <table width="596" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="640"> 
        <table width="586" border="0" align="center" >
		  <tr> 
            <td  align="left" colspan="8"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>
          <tr> 
		     <td width="56"   align="left"><font size="-1">
              產品編號</font> 
            </td>                     
            <td width="61"  align="left"><font size="-1"> 
             產品名稱</font>
            </td>
            <td width="60"  align="left"><font size="-1"> 
             銷貨單號</font>
            </td>           
            <td width="71"  align="left"><font size="-1"> 
              銷貨日期</font>
            </td>			
			<td width="62" align="left"><font size="-1"> 
             客戶</font> 
            </td> 
			 <td width="68"  align="left"><font size="-1"> 
             銷貨數量</font> 
            </td>  
			 <td width="54" align="left"><font size="-1"> 
             售價</font>
            </td>      
			 <td width="70" align="left"><font size="-1"> 
              金額</font>
            </td>                  
          </tr>
		  <tr> 
            <td  align="left" colspan="8"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>		  
	<?php
//--------------選擇頁數銷貨單資料呈現及連接頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=30*($page - 1);
	  $SQLStr="select * from outinv   WHERE (outiprodno >='$outiprodno1' and outiprodno<='$outiprodno2') limit $first , 30";
	  $res = mysql_query($SQLStr);	  
      while (list($outicode, $outino, $outiprodno, $outidate, $outiremark, $outicustno, $outiprodname, $outiprodqty, $outiunit, $outipric, $outiamt)=mysql_fetch_row($res))
			{
//------------------------- 抓取資料表中資料並呈現銷貨紀錄------------------
             echo "<tr border='0'   >";	
			echo "<td align='left'><font size='-1'>" . $outiprodno . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outiprodname . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outino  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outidate  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outicustno . "</font></td>\n";			
			echo "<td align='left'><font size='-1'>" . $outiprodqty . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outipric . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outiamt . "</font></td>\n";	
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
