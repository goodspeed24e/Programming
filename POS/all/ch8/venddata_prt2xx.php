<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��venddata2_prt2</title>
</head>
<body>
<?php
		include("mysqlcntdb.php"); 
//----------------���X�ŦX������,�j�M�t�Ӹ��,�N�ŦX�϶�����ƨ��X----------------------		
		$SQLStr3 = "SELECT * FROM vend WHERE (vendno >='$vendno1' and vendno <='$vendno2')";		
		$res = mysql_query($SQLStr3);
		$j=mysql_num_rows($res);
?>
<body onLoad="window.print()"> 
<!------�j�M����,�^����----------------------->
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="924" border="0" align="center">
    <tr>
      <td width="914">
        <table width="100%" border="0">
          <tr>
            <td>
              <div align="center">�t�Ӹ�ƪ�</div>
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
              <div align="center">�t�ӽs��</div>
            </td>
            <td height="23" width="84"> 
              <div align="center">�t�ӦW��</div>
            </td>
			 <td height="23" width="100"> 
              <div align="center">�t��²��</div>
            </td>			
            <td height="23" width="97"> 
              <div align="center">�t�d�H</div>
            </td>
            <td width="99" height="23"> 
              <div align="center">�Τ@�s��</div>
            </td>
            <td height="23" width="90"> 
              <div align="center">�p���H</div>
            </td>
            <td width="97" height="23"> 
              <div align="center">�p���q��</div>
            </td>
            <td width="104" height="23"> 
              <div align="center">�p�����</div>
            </td>
			<td width="111" height="23"> 
              <div align="center"></div>
            </td>
          </tr>
		  <tr> 
           	<td height="23" width="88"> 
              <div align="center">�ǯu��</div>
            </td>
            <td height="23" width="84"> 
              <div align="center">�Ȥ����O</div>
            </td>
			 <td height="23" width="100"> 
              <div align="center">�~�Ⱦ��</div>
            </td>
			 <td height="23" width="97" colspan="3"> 
              <div align="center">�t�Ӧa�}</div>
            </td>
		  </tr>
		  <tr>
            <td height="23"  colspan="3"> 
              <div align="center">�o���a�}</div>
            </td>
            <td height="23" colspan="3"> 
              <div align="center">�e�f�a�}</div>
            </td>			 
            <td height="23" width="97"> 
              <div align="center">�H�c</div>
            </td>		  
            <td width="104" height="23"> 
              <div align="center">���}</div>
            </td>		   
            <td width="111" height="23"> 
              <div align="center">���ɤ��</div>
            </td> 
		   </tr>
		   <tr>             
			<td height="23" width="88"> 
              <div align="center">�̪񲧰ʤ�</div>
            </td>
            <td height="23" width="84"> 
              <div align="center">������O</div>
            </td>
			 <td height="23" width="100"> 
              <div align="center">���ڧ��</div>
            </td>
			 <td height="23" width="97"> 
              <div align="center">�W�����B</div>
            </td>
            <td height="23" width="99"> 
              <div align="center">�������B</div>
            </td>
            <td width="90" height="23"> 
              <div align="center">�䲼���B</div>
            </td>
            <td height="23" width="97"> 
              <div align="center">�W�����</div>
            </td>
            <td width="104" height="23"> 
              <div align="center">�i�f���</div>
            </td>
			<td width="111" height="23"> 
              <div align="center">�䲼���</div>
            </td>           
          </tr>
<? 
//--------------Ū����ƪ�,�Y�t�Ӹ�ƪ����j�M���Ƥ��e-----------------------------------	
	if (mysql_num_rows($res)>0)
	{
	  $num = mysql_num_rows($res);	 
//-------------�e�{�C�L���e,�t�Ӹ��-------------------------------------------------- 
	  for ($i=0;$i<$num;$i++)
	  {
		$row = mysql_fetch_array($res);
//-------------�{���j����浲��, �Y�j�M���G�w�L���-----------------------------------				
		if(!$row) 
//------------�j��X�f,����{�Ǥ��_����----------------------------------------------		
			break; 
//------------��ƦC�L���e�e�{,�t�Ӹ�Ʃ���--------------------------------------------			
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
                <input type="button" name="windowsclose" value="����" onClick="window.close();">
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
