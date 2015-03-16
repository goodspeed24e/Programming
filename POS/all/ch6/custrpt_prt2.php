<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body onLoad="window.print()">
<?php
		include("mysqlcntdb.php"); 
		$SQLStr3 = "SELECT * FROM cust WHERE (custno >='$custno1' and custno <='$custno2')";		
		$res = mysql_query($SQLStr3);
		$j=mysql_num_rows($res);

?>
<form name="form1" method="post" action="../index.php">
  <table width="924" border="0" align="center">
    <tr>
      <td width="914">
        <table width="100%" border="0">
          <tr>
            <td>
              <div  align="left">客戶一覽表</div>
            </td>
          </tr>
		  <tr>	
		  <td align='left'  height='21'><font size='-1'>編號: <?php echo $custno1 ?> 至 <?php echo $custno2 ?></font></td>
		  </tr>	
        </table>
        <table width="100%" border="0">
          <tr> 
            <td colspan="7"> 
              <hr size="1" color="#000000" width="100%">
            </td>
          </tr>
          <tr>           
			<td height="23" width="70"><font size="-1">
              <div  align="left">客戶編號</div></font> 
            </td>
            <td height="23" width="77"><font size="-1"> 
              <div align="left">客戶簡稱</div></font>
            </td>
			 <td height="23" width="67"><font size="-1"> 
              <div align="left">統一編號</div></font>
            </td>			
            <td height="23" width="58"><font size="-1"> 
              <div align="left">聯絡人</div></font>
            </td>
            <td width="73" height="23"><font size="-1"> 
              <div align="left">聯絡電話</div></font>
            </td>
            <td height="23" width="80"><font size="-1"> 
              <div align="left">聯絡手機</div></font>
            </td>
            <td width="421" height="23" colspan="3"><font size="-1"> 
              <div align="left">客戶地址</div></font>
            </td>           
          </tr>
		   <tr> 
            <td colspan="7"> 
              <hr size="1" color="#000000" width="100%">
            </td>
          </tr>
		 
<? 
	// 若客戶資料表中有客戶資料
	if (mysql_num_rows($res)>0)
	{
	  $num = mysql_num_rows($res);	 
	  // 呈現客戶資料表內容
	  for ($i=0;$i<$num;$i++)
	  {
		$row = mysql_fetch_array($res);		
		if(!$row) 
			break; 		
		echo "<tr>";	
		echo "<td width='50' height='21' align='left'><font size='-1'>" . $row['custno'] . "</font></td>";
		echo "<td width='60' height='21' align='left'><font size='-1'>" . $row['custsname'] . "</font></td>";
		echo "<td width='80' height='21' align='left'><font size='-1'>". $row['custinvoice'] . "</font></td>";
		echo "<td width='80' height='21' align='left'><font size='-1'>". $row['custcontact'] . "</font></td>";
		echo "<td width='80' height='21' align='left'><font size='-1'>". $row['custtel'] . "</font></td>";
		echo "<td align='left' width='80' height='21'><font size='-1'>" . $row['custmobil'] . "</font></td>";
		echo "<td width='200' height='21' align='left'><font size='-1'>" . $row['custadr'] . "</font></td></tr>";			
		echo " <tr> 
            <td colspan='7'>
		         <hr size='1' color='#999999' width='100%'>
            </td>
          </tr>";
	  }
	}
?>
        </table>
        <hr>
        <table width="100%" border="0">
          <tr >             
            <td height="23"> 
              <div  align="center"> 
                <input type="button" name="CONT" value="結束" onClick="window.close();">
              </div>
            </td>
            <td height="23" > 
              <div align="left">
                &nbsp;
              </div>
            </td>
          </tr>
          <tr>
            <td colspan="4" align='center'>
            </td>
          </tr>
        </table>
      </td>
    </tr>
  </table>
  </form> 
</body>
</html>
