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
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="924" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr>
      <td width="914">
        <table width="100%" border="0">
          <tr>
            <td>
              <div  align="left">客戶會計科目設定表</div>
            </td>
          </tr>
		  <tr>	
		  <td align='left'  height='21'><font size='-1'>編號: <?php echo $custno1 ?> 至 <?php echo $custno2 ?></font></td>
		  </tr>	
        </table>
        <table width="100%" border="0" cellpadding="0" cellspacing="0">
          <tr> 
            <td  align="left" colspan="9"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>
          <tr>           
			<td height="23" width="63"><font size="-1"> 
              <div  align="left">客戶編號</div></font>
            </td>
            <td height="23" width="62"><font size="-1"> 
              <div align="left">客戶簡稱</div></font>
            </td>
			 <td height="23" width="62"><font size="-1"> 
              <div align="left">統一編號</div></font>
            </td>			
            <td height="23" width="48"><font size="-1"> 
              <div align="left">聯絡人</div></font>
            </td>
            <td width="65" height="23"><font size="-1"> 
              <div align="left">聯絡電話</div></font>
            </td>
            <td width="67" height="23" ><font size="-1"> 
              <div align="left">聯絡手機</div></font>
            </td>
            <td width="79" height="23" > 
              <div align="left"><font size="-1">預收科目</font></div>
            </td>
			 <td width="82" height="23" > 
              <div align="left"><font size="-1">應收科目</font></div>
            </td>   
			 <td width="386"  height="23" > 
              <div align="left"><font size="-1">支票科目</font></div>
            </td>              
          </tr>	
		    <tr> 
            <td  align="left" colspan="9"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>		
<?php 
//---------- 若客戶資料表中有資料內容---------- 	
	if (mysql_num_rows($res)>0)
	{
	  $num = mysql_num_rows($res);	 
//---------- 呈現客戶資料表內容---------------- 
	  for ($i=0;$i<$num;$i++)
	  {
		$row = mysql_fetch_array($res);	
// 若結果列中已無資料,結束執行			
		if(!$row) 
			break; 
		echo "<tr>";		
		echo "<td width='60' height='21' align='left'><font size='-1'>" . $row['custno'] . "</font></td>";
		echo "<td width='60' height='21' align='left'><font size='-1'>" . $row['custsname'] . "</font></td>";
		echo "<td width='100' height='21' align='left'><font size='-1'>". $row['custinvoice'] . "</font></td>";
		echo "<td width='100' height='21' align='left'><font size='-1'>". $row['custcontact'] . "</font></td>";
		echo "<td width='100' height='21' align='left'><font size='-1'>". $row['custtel'] . "</font></td>";
		echo "<td align='left' width='60' height='21'><font size='-1'>" . $row['custmobil'] . "</font></td>";
		echo "<td  height='21' align='left'><font size='-1'>" . $row['custprepdc'] . "</font></td>";
		echo "<td align='left'  height='21'><font size='-1'>" . $row['custsaledc'] . "</font></td>";
		echo "<td align='left'  height='21'><font size='-1'>" . $row['custchkdc'] . "</font></td></tr>";
		echo "  <tr> 
            <td colspan='9'> 
              <hr>
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
                <input type="button" name="windowsclose" value="結束" onClick="window.close();">
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
