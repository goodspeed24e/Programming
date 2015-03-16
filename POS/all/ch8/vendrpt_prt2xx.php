<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統vendrpt_prt2</title>
</head>
<body onLoad="window.print()">
<?php
		include("mysqlcntdb.php"); 
//----------------取出符合條件資料,搜尋廠商資料,將符合區間內資料取出----------------------		
		$SQLStr3 = "SELECT * FROM vend WHERE (vendno >='$vendno1' and vendno <='$vendno2')";		
		$res = mysql_query($SQLStr3);
		$j=mysql_num_rows($res);	
?>
<!---執行完成,回首頁----->
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="924" border="0" align="center">
    <tr>
      <td width="914">
        <table width="100%" border="0">
          <tr>
            <td>
              <div align="center">廠商一覽表</div>
            </td>
          </tr>
        </table>
        <table width="100%" border="0">
          <tr> 
            <td colspan="10"> 
              <hr>
            </td>
          </tr>
          <tr>           
			<td height="23" width="79"> 
              <div align="center">廠商編號</div>
            </td>
            <td height="23" width="77"> 
              <div align="center">廠商簡稱</div>
            </td>
			 <td height="23" width="67"> 
              <div align="center">統一編號</div>
            </td>			
            <td height="23" width="58"> 
              <div align="center">聯絡人</div>
            </td>
            <td width="73" height="23"> 
              <div align="center">聯絡電話</div>
            </td>
            <td height="23" width="84"> 
              <div align="center">聯絡手機</div>
            </td>
            <td width="440" height="23" colspan="3"> 
              <div align="center">客戶地址</div>
            </td>           
          </tr>
		
<?php	
//--------------讀取資料表,若廠商資料表中有搜尋到資料內容-----------------------------------	
	if (mysql_num_rows($res)>0)
	{
	  $num = mysql_num_rows($res);
//-------------呈現列印內容,廠商資料-------------------------------------------------- 
	  for ($i=0;$i<$num;$i++)
	  {
		$row = mysql_fetch_array($res);	
//-------------程式迴圈執行結束, 若搜尋結果已無資料-----------------------------------	
		if(!$row)
//------------迴圈出口,後續程序中斷執行----------------------------------------------	
			break;  
//------------資料列印內容呈現,廠商資料明細--------------------------------------------			
		echo "<tr>";		
		echo "<td width='60' height='21' align='center'>" . $row['vendno'] . "</td>";
		echo "<td width='60' height='21' align='center'>" . $row['vendsname'] . "</td>";
		echo "<td width='100' height='21' align='center'>". $row['vendinvoice'] . "</td>";
		echo "<td width='100' height='21' align='center'>". $row['vendcontact'] . "</td>";
		echo "<td width='100' height='21' align='center'>". $row['vendtel'] . "</td>";
		echo "<td align='center' width='60' height='21'>" . $row['vendmobil'] . "</td>";
		echo "<td width='200' height='21' align='center'>" . $row['vendadr'] . "</td></tr>";			
		echo "  <tr> 
            <td colspan='10'> 
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
