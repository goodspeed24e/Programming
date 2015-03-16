<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<?php
		include("mysqlcntdb.php"); 
		$SQLStr3 = "SELECT * FROM cust WHERE (custno >='$custno1' and custno <='$custno2')";		
		$res = mysql_query($SQLStr3);
		$j=mysql_num_rows($res);
?>
<body onLoad="window.print()"> 
<!------ 回首頁  ------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="924" border="0" align="center">
    <tr>
      <td width="914">
        <table width="100%" border="0">
          <tr>
            <td>
              <div   align="left">客戶資料表</div>
            </td>
          </tr>
		    <tr>	
		  <td align='left'  height='21'><font size='-1'>編號: <?php echo $custno1 ?> 至 <?php echo $custno2 ?></font></td>
		  </tr>	
        </table>
        <table width="83%" border="0">
          <tr> 
            <td colspan="8"> 
              <hr color="#000000" size="2" width="100%">
            </td>
          </tr>
          <tr>          
			<td height="23" width="73"><font size="-1">  
              <div align="left">客戶編號</div></font>
            </td>
            <td height="23" colspan="2"><font size="-1">  
              <div align="left">客戶名稱</div></font>
            </td>
			 <td height="23" width="69"><font size="-1">  
              <div align="left">簡稱</div></font>
            </td>			
            <td height="23" width="64"><font size="-1">  
              <div align="left">負責人</div></font>
            </td>
            <td width="69" height="23"><font size="-1">  
              <div align="left">統一編號</div></font>
            </td>
            <td height="23" width="70"><font size="-1">  
              <div align="left">聯絡人</div></font>
            </td>
            <td width="221" height="23"><font size="-1">  
              <div align="left">聯絡電話</div></font>
            </td>           
			
          </tr>
		  <tr> 
           	<td height="23" width="73"><font size="-1">  
              <div align="left">傳真機</div></font>
            </td>
            <td height="23" width="88"><font size="-1">  
              <div align="left">客戶別</div></font>
            </td>
			 <td height="23" width="67"><font size="-1">  
              <div align="left">業務擔當</div></font>
            </td>
			 <td height="23"  colspan="5"><font size="-1">  
              <div  align="left">客戶地址</div></font>
            </td>
		  </tr>
		  <tr>
            <td height="23"  colspan="3"><font size="-1">  
              <div  align="left">發票地址</div></font>
            </td>
            <td height="23" colspan="3"><font size="-1">  
              <div  align="left">送貨地址</div></font>
            </td>			 
            <td height="23"  colspan="2"><font size="-1">  
              <div align="left">信箱</div></font>
            </td>		  
           
	      </tr>
		   <tr>             
			<td height="23" width="73"><font size="-1">  
              <div align="left">最近異動日</div></font>
            </td>
            <td height="23" width="88"><font size="-1">  
              <div align="left">售價別</div></font>
            </td>
			 <td height="23" width="67"><font size="-1">  
              <div align="left">收款折數</div></font>
            </td>
			 <td height="23" width="69"><font size="-1">  
              <div align="left"><font size="-1">上期金額</font></div>
            </td>
            <td height="23" width="64"><font size="-1">  
              <div align="left">本期金額</div></font>
            </td>
            <td width="69" height="23"><font size="-1">  
              <div align="left">支票金額</div></font>
            </td>
             <td width="70" height="23"><font size="-1">  
              <div align="left">網址</div></font>
            </td>		   
            <td width="221" height="23"><font size="-1">  
              <div align="left">建檔日期</div></font>
            </td>      
          </tr>
		  <tr> 
            <td colspan="8"> 
              <hr color="#000000" size="2" width="100%">
            </td>
          </tr>
<? 
//--------------- 若客戶資料表中有內容 ---------------
	if (mysql_num_rows($res)>0)
	{
	  $num = mysql_num_rows($res);	 
//-----------------列印符合條件資料內容-----------------	 
	  for ($i=0;$i<$num;$i++)
	  {
		$row = mysql_fetch_array($res);		
		if(!$row) 
			break; 
		echo "<tr>";		
		    echo "<td width='30' height='21' align='left'><font size='-1'>" . $row['custno'] . "</font></td>";	
		    echo "<td width='120' height='21' align='left' colspan='2'><font size='-1'>" . $row['custname'] . "</font></td>";	
		        echo "<td width='60' height='21' align='left'><font size='-1'>". $row['custsname'] . "</font></td>";	
		        echo "<td width='60' height='21' align='left'><font size='-1'>". $row['custleader'] . "</font></td>";	
		        echo "<td width='60' height='21' align='left'><font size='-1'>". $row['custinvoice'] . "</font></td>";	
		        echo "<td align='left' width='60' height='21'><font size='-1'>" . $row['custcontact'] . "</font></td>";	
		        echo "<td width='60' height='21' align='left'><font size='-1'>" . $row['custtel'] . "</font></td></tr>";
		    echo "<tr>";		
		        echo "<td width='80' height='21'  align='left'><font size='-1'>" . $row['custfax'] . "</font></td>";	
		        echo "<td width='60' height='21' align='left'><font size='-1'>" . $row['custtype'] . "</font></td>";	
		        echo "<td width='60' height='21' align='left'><font size='-1'>" . $row['custsales'] . "</font></td>";	
		        echo "<td width='260' height='21' align='left' colspan='4'><font size='-1'>" . $row['custadr'] . "</font></td></tr>";	
		   echo "<tr>";	
		        echo "<td width='200' height='21' align='left' colspan='3'><font size='-1'>". $row['custpradr'] . "</font></td>";		
		        echo "<td width='200' height='21' align='left' colspan='3'><font size='-1'>". $row['custinadr'] . "</font></td>";			
		        echo "<td align='left' width='100' height='21' colspan='2'><font size='-1'>" . $row['custemail'] . "</font></td></tr>";			       
		    echo "<tr>";	
		        echo "<td width='80' height='21' align='left'><font size='-1'>" . $row['custclosdate'] . "</font></td>";			
		        echo "<td align='left' width='80' height='21'><font size='-1'>" . $row['custprictype'] . "</font></td>";	
		        echo "<td width='60' height='21' align='left'><font size='-1'>" . $row['custpricper'] . "</font></td>";	
		        echo "<td width='60' height='21' align='left'><font size='-1'>" . $row['custprepamt'] . "</font></td>";	
		        echo "<td width='100' height='21' align='left'><font size='-1'>". $row['custsaleamt'] . "</font></td>";	
		        echo "<td width='100' height='21' align='left'><font size='-1'>". $row['custchkamt'] . "</font></td>";	
		        echo "<td align='left' width='10' height='21'><font size='-1'>" . $row['custhttp']  . "</font></td>";	
		        echo "<td width='100' height='21' align='left'><font size='-1'>" . $row['custdate']  . "</font></td></tr>";			       	
		    echo "<tr> 
                <td colspan='8'> 
                <hr>
                </td>
                </tr>";
	  }
	}	
?>        
        </table>      
        <table width="100%" border="0">
          <tr >
            <td width="83%" height="23"> 
              <div  align="center"> 
                <input type="button" name="windowclose" value="結束" onClick="window.close();">
              </div>
            </td>
            <td width="17%" height="23" > 
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
