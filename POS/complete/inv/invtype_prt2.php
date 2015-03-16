<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body onLoad="window.print()">
<?php
// -------------取出選擇的產品類別的資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT product.* FROM product WHERE (prodtype='$prodtype') ";	
	$res = mysql_query($SQLStr);

//--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/30);
?>
<!------搜尋完成,回首頁----------------------->
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="587" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td  align="left">
		 <?php
//--------------頁數選擇呈現及連接---------------
     echo "產品類別明細表&nbsp;&nbsp;<br><font size='-1'>產品類別編號:&nbsp;&nbsp;".$prodtype. "&nbsp;&nbsp;第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=326&page=$i>$i</a>|";
	}
       echo "頁, 共".$total."筆&nbsp;&nbsp</font>";
?>   
    </td>
    </tr>
  </table>
  <table width="593" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="593"> 
        <table width="589" border="0"  align="left">
		  <tr> 
          <td  align="left" colspan="7"> 
            <hr  size="1" color="#000000"  width="100%">
          </td>
		  </tr>
          <tr>                     
            <td width="67" align="left" ><font size="-1">
             產品編號</font> 
            </td>
            <td width="83" align="left" ><font size="-1"> 
             產品名稱</font>
            </td>
            <td width="108" align="left" ><font size="-1"> 
              規格說明</font>
            </td>
            <td width="90" align="left" ><font size="-1"> 
              產品分類</font>
            </td>
			 <td width="73" align="left" ><font size="-1"> 
              進價</font>
            </td> 
			<td width="65" align="left" ><font size="-1"> 
              售價</font>
            </td>     
			 <td width="73" align="left" ><font size="-1"> 
              庫存數</font>
            </td>                  
          </tr>
		    <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
			</tr>		  
	<?php
//--------------選擇頁數產品分類資料呈現及連接頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=30*($page - 1);
	  $SQLStr="select * from product WHERE (prodtype='$prodtype') limit $first , 30";
	  $res = mysql_query($SQLStr);	
       while (list($prodno, $prodname, $prodtype, $prodvend, $produnit, $prodipric, $prodspric, $prodsave, $prodpqty, $prodnqty, $prodgrap, $prodsdesp, $proddesp, $prodidate, $prododate)=mysql_fetch_row($res))
		{
//------------資料列印內容呈現,產品分類資料明細--------------------------------------------	
            echo "<tr border='0'   >";	
			echo "<td align='left'><font size='-1'>" . $prodno  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodname . "</font></td>\n";
			echo "<td align='left'><font size='-1'>";
			if ($prodsdesp == '') 
		         $prodsdesp="無規格說明";	        
			echo  $prodsdesp . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodtype . "</font></td>\n";		
			echo "<td align='left'><font size='-1'>" . $prodipric . "</font></td>\n";
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
