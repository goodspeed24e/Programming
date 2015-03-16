<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body onLoad="window.print()">
<?php
// -------------取出所有呆滯產品的資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT product.* FROM product WHERE (prodidate <='$proddate' and prododate<='$proddate') ";	
	$res = mysql_query($SQLStr);
	
//--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/30);
?>
<!------搜尋完成,回首頁----------------------->
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="594" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td width="590" align="left">
		 <?php
//--------------頁數選擇呈現及連接---------------
     echo "呆滯產品明細表&nbsp;&nbsp; <br><font size='-1'>最後異動日期:".$proddate."第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=../index.php?Select=345&page=$i>$i</a>|";
	}
       echo "頁, 共".$total."筆&nbsp;&nbsp</font>";
?> 	  
    </td>
    </tr>
  </table>
  <table width="593" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="691"> 
        <table width="593" border="0" align="center" >
		 <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>
          <tr>                     
            <td width="62"  align="left"><font size="-1">  
             產品編號</font>
            </td>
            <td width="89"  align="left"><font size="-1">  
             產品名稱</font>
            </td>
            <td width="73"  align="left"><font size="-1">  
              規格說明</font>
            </td>
            <td width="86"  align="left"><font size="-1">  
              最近進貨日</font>
            </td>
			 <td width="78" align="left"><font size="-1">  
               最近出貨日</font>
            </td> 
			<td width="63"  align="left"><font size="-1">  
              售價</font>
            </td>     
			 <td width="96"  align="left"><font size="-1">  
              庫存數</font>
            </td>                  
          </tr>
		   <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>		  
	<?php
//--------------選擇頁數產品資料呈現及連接頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=30*($page - 1);
	  $SQLStr="select * from product WHERE (prodidate <='$proddate' and prododate<='$proddate') limit $first , 30";
	  $res = mysql_query($SQLStr);	
       while (list($prodno, $prodname, $prodtype, $prodvend, $produnit, $prodipric, $prodspric, $prodsave, $prodpqty, $prodnqty, $prodgrap, $prodsdesp, $proddesp, $prodidate, $prododate)=mysql_fetch_row($res))
		{
//------------資料列印內容呈現,呆滯產品資料明細--------------------------------------------
            echo "<tr border='0'   >";	
			echo "<td align='left'><font size='-1'>" . $prodno  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodname . "</font></td>\n";
			echo "<td align='left'><font size='-1'>";
			if ($prodsdesp == '') 
		         $prodsdesp="無規格說明";	        
			echo  $prodsdesp . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodidate . "</font></td>\n";		
			echo "<td align='left'><font size='-1'>" . $prododate  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodspric . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodnqty . "</font></td>\n";
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
