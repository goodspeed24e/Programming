<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統venddata2_prt2</title>
</head>
<body>
<?php
		include("mysqlcntdb.php"); 
//----------------取出符合條件資料,搜尋廠商資料,將符合區間內資料取出----------------------		
		$SQLStr3 = "SELECT * FROM vend WHERE (vendno >='$vendno1' and vendno <='$vendno2')";		
		$res = mysql_query($SQLStr3);
		$j=mysql_num_rows($res);
?>
<body onLoad="window.print()"> 
<!------搜尋完成,回首頁----------------------->
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="924" border="0" align="center">
    <tr>
      <td width="914">
        <table width="100%" border="0">
          <tr>
            <td>
              <div align="center">廠商資料表</div>
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
          
			<td height="23" width="88"> 
              <div align="center">廠商編號</div>
            </td>
            <td height="23" width="84"> 
              <div align="center">廠商名稱</div>
            </td>
			 <td height="23" width="100"> 
              <div align="center">廠商簡稱</div>
            </td>			
            <td height="23" width="97"> 
              <div align="center">負責人</div>
            </td>
            <td width="99" height="23"> 
              <div align="center">統一編號</div>
            </td>
            <td height="23" width="90"> 
              <div align="center">聯絡人</div>
            </td>
            <td width="97" height="23"> 
              <div align="center">聯絡電話</div>
            </td>
            <td width="104" height="23"> 
              <div align="center">聯絡手機</div>
            </td>
			<td width="111" height="23"> 
              <div align="center"></div>
            </td>
          </tr>
		  <tr> 
           	<td height="23" width="88"> 
              <div align="center">傳真機</div>
            </td>
            <td height="23" width="84"> 
              <div align="center">客戶類別</div>
            </td>
			 <td height="23" width="100"> 
              <div align="center">業務擔當</div>
            </td>
			 <td height="23" width="97" colspan="3"> 
              <div align="center">廠商地址</div>
            </td>
		  </tr>
		  <tr>
            <td height="23"  colspan="3"> 
              <div align="center">發票地址</div>
            </td>
            <td height="23" colspan="3"> 
              <div align="center">送貨地址</div>
            </td>			 
            <td height="23" width="97"> 
              <div align="center">信箱</div>
            </td>		  
            <td width="104" height="23"> 
              <div align="center">網址</div>
            </td>		   
            <td width="111" height="23"> 
              <div align="center">建檔日期</div>
            </td> 
		   </tr>
		   <tr>             
			<td height="23" width="88"> 
              <div align="center">最近異動日</div>
            </td>
            <td height="23" width="84"> 
              <div align="center">售價類別</div>
            </td>
			 <td height="23" width="100"> 
              <div align="center">收款折數</div>
            </td>
			 <td height="23" width="97"> 
              <div align="center">上期金額</div>
            </td>
            <td height="23" width="99"> 
              <div align="center">本期金額</div>
            </td>
            <td width="90" height="23"> 
              <div align="center">支票金額</div>
            </td>
            <td height="23" width="97"> 
              <div align="center">上期科目</div>
            </td>
            <td width="104" height="23"> 
              <div align="center">進貨科目</div>
            </td>
			<td width="111" height="23"> 
              <div align="center">支票科目</div>
            </td>           
          </tr>
<? 
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
		echo "<td width='60' height='21' align='center'>" . $row['vendname'] . "</td>";
		echo "<td width='200' height='21' align='center'>". $row['vendsname'] . "</td>";
		echo "<td width='200' height='21' align='center'>". $row['vendleader'] . "</td>";
		echo "<td width='100' height='21' align='center'>". $row['vendinvoice'] . "</td>";
		echo "<td align='center' width='10' height='21'>" . $row['vendcontact'] . "</td>";
		echo "<td width='10' height='21' align='center'>" . $row['vendtel'] . "</td>";
		echo "<td width='60' height='21' align='center'>" . $row['vendmobil'] . "</td>";		
		echo "<td width='10' height='21' align='center'></td></tr>";
		echo "<tr>";	
		echo "<td width='80' height='21'  align='center'>" . $row['vendfax'] . "</td>";
		echo "<td width='60' height='21' align='center'>" . $row['vendtype'] . "</td>";
		echo "<td width='60' height='21' align='center'>" . $row['vendsales'] . "</td>";
		echo "<td width='60' height='21' align='center'>" . $row['vendadr'] . "</td></tr>";
		echo "<tr>";
		echo "<td width='200' height='21' align='center' colspan='3'>". $row['vendpradr'] . "</td>";		
		echo "<td width='100' height='21' align='center' colspan='3'>". $row['vendinadr'] . "</td>";		
		echo "<td align='center' width='10' height='21'>" . $row['vendemail'] . "</td>";
		echo "<td width='10' height='21' align='center'>" . $row['vendhttp'] . "</td>";		    
		echo "<td width='80' height='21' align='center'>" . $row['venddate'] . "</td></tr>";
		echo "<tr>";
		echo "<td width='80' height='21' align='center'><font size='-1'>" . $row['vendclosdate'] . "</font></td>";		
		echo "<td align='center' width='80' height='21'>" . $row['vendprictype'] . "</td>";
		echo "<td width='60' height='21' align='center'>" . $row['vendpricper'] . "</td>";
		echo "<td width='60' height='21' align='center'>" . $row['vendprepamt'] . "</td>";
		echo "<td width='200' height='21' align='center'>". $row['vendapamt'] . "</td>";
		echo "<td width='100' height='21' align='center'>". $row['vendchkamt'] . "</td>";
		echo "<td align='center' width='10' height='21'>" . $row['vendprepdc'] . "</td>";
		echo "<td width='10' height='21' align='center'>" . $row['vendapdc'] . "</td>";
		echo "<td width='60' height='21' align='center'>" . $row['vendchkdc'] . "</td></tr>";		
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
