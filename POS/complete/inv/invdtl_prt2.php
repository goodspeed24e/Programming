<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body onLoad="window.print()">
<?php
// -------------取出所有選擇的產品資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT product.* FROM product WHERE (prodno >='$prodno1' and prodno<='$prodno2') ";	
	$res = mysql_query($SQLStr);

//--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/30);
?>
<!------搜尋完成,回首頁----------------------->
<form name="form1" method="post" action="../index.php?Select=10">

  <table width="659" border="0"  align="center" cellspacing="0" cellpadding="0" >
<?php  
    echo " <tr > ";
      echo "<td  align='left'>";		
//--------------頁數選擇呈現及連接---------------
     echo "產品明細表&nbsp;&nbsp; <br>產品編號:".$prodno1."至".$prodno2."&nbsp;&nbsp;第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=326&page=$i>$i</a>|";
	}
       echo "頁, 共".$total."筆&nbsp;&nbsp";
    echo "</td>";
    echo "</tr>";
?>	
  </table>
<!------搜尋完成,回首頁----------------------->  
  <table width="659" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="647"> 
        <table width="592" border="0" align="left" >
		   <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>
          <tr>                     
            <td width="69"  align="left"><font size="-1"> 
             產品編號</font>
            </td>
            <td width="91"  align="left"><font size="-1">  
             產品名稱</font>
            </td>
            <td width="76"  align="left"><font size="-1">  
              規格說明</font>
            </td>
            <td width="73"  align="left"><font size="-1">  
              廠商</font>
            </td>
			 <td width="55" align="left"><font size="-1">  
              進價</font>
            </td> 
			<td width="85"  align="left"><font size="-1">  
              售價</font>
            </td>     
			 <td width="113" align="left"><font size="-1">  
              庫存數</font>
            </td>                  
          </tr>	
		   <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>	  
	<?php
//--------------讀取資料表,若產品資料表中有搜尋到資料內容-----------------------------------	
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=30*($page - 1);	  
	  $SQLStr="select * from product WHERE (prodno >='$prodno1' and prodno<='$prodno2') limit $first , 30";
	  $res = mysql_query($SQLStr);	
       while (list($prodno, $prodname, $prodtype, $prodvend, $produnit, $prodipric, $prodspric, $prodsave, $prodpqty, $prodnqty, $prodgrap, $prodsdesp, $proddesp, $prodidate, $prododate)=mysql_fetch_row($res))
		{
//------------資料列印內容呈現,產品資料明細--------------------------------------------	
            echo "<tr border='0'   >";	
			echo "<td align='left'><font size='-1'>" . $prodno  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodname . "</font></td>\n";
			echo "<td align='left'><font size='-1'>";
			if ($prodsdesp == '') 
		         $prodsdesp="無規格說明";	        
			echo  $prodsdesp . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodvend . "</font></td>\n";		
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
