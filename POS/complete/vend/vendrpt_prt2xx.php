<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��vendrpt_prt2</title>
</head>
<body onLoad="window.print()">
<?php
		include("mysqlcntdb.php"); 
//----------------���X�ŦX������,�j�M�t�Ӹ��,�N�ŦX�϶�����ƨ��X----------------------		
		$SQLStr3 = "SELECT * FROM vend WHERE (vendno >='$vendno1' and vendno <='$vendno2')";		
		$res = mysql_query($SQLStr3);
		$j=mysql_num_rows($res);	
?>
<!---���槹��,�^����----->
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="924" border="0" align="center">
    <tr>
      <td width="914">
        <table width="100%" border="0">
          <tr>
            <td>
              <div align="center">�t�Ӥ@����</div>
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
              <div align="center">�t�ӽs��</div>
            </td>
            <td height="23" width="77"> 
              <div align="center">�t��²��</div>
            </td>
			 <td height="23" width="67"> 
              <div align="center">�Τ@�s��</div>
            </td>			
            <td height="23" width="58"> 
              <div align="center">�p���H</div>
            </td>
            <td width="73" height="23"> 
              <div align="center">�p���q��</div>
            </td>
            <td height="23" width="84"> 
              <div align="center">�p�����</div>
            </td>
            <td width="440" height="23" colspan="3"> 
              <div align="center">�Ȥ�a�}</div>
            </td>           
          </tr>
		
<?php	
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
