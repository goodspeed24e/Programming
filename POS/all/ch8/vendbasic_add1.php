<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?	
	include("mysqlcntdb.php");
	$cntid="vend";
	include("counter.php");
//----------------------- �N�t�����O��ƪ�����ƥ������X-------------------------- 
	$SQLStr = "SELECT * FROM vety";
	$res = mysql_query($SQLStr);
	
?>
<!--����t�Ӱ򥻸�ƿ�J��,�i�Jvendbasic_add2.php�s����Ʈw------->
<form name="form1" method="post" action="vend/vendbasic_add2.php">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td bgcolor="#ffffff"> 
        <table width="780" border="0" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">�t�Ӱ򥻸��</font>
            </td>
            <td align="center"> 
              <input type="submit" name="submit" value="�s�W�t��">
            </td>
	  </tr>
        </table>
<!--�t�Ӱ򥻸�ƿ�J------->		
        <table width="780" border="1" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
          <tr> 
            <td width="103" align="center">�t�ӧǸ�</td>
            <td width="187"> 
                <input type="text" name="vendno" size="10" value="<?=$vendcnt;?>">
            </td>
            <td width="96" align="center">�t��²��</td>
            <td width="351"> 
                <input type="text" name="vendsname" size="30">
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">���q�W��</td>
            <td width="187"> 
                 <input type="text" name="vendname" size="40">
            </td>
            <td width="96" align="center">�t�d�H</td>
            <td width="351"> 
                <input type="text" name="vendleader" size="10">
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">�Τ@�s��</td>
            <td width="187"> 
                <input type="text" name="vendinvoice" size="10">
            </td>
            <td width="96" align="center">�p���H</td>
            <td width="351"> 
                <input type="text" name="vendcontact" size="10">
            </td>
          </tr>
		   <tr> 
            <td width="103" align="center">�p���q��</td>
            <td width="187"> 
                <input type="text" name="vendtel" size="10">
            </td>
            <td width="96" align="center">�p�����</td>
            <td width="351"> 
                <input type="text" name="vendmobil" size="10">
            </td>
          </tr>
          <tr> 
            <td width="103" height="22" align="center">�ǯu��</td>
            <td width="187" height="22"> 
              <input type="text" name="vendfax" size="10">
            </td>
            <td width="96" height="22" align="center">�t�����O</td>
           <!-- </td>-->
            <td width="187" height="22">
<?
	if ($res)
	{
	  $num = mysql_num_rows($res);
//---------- �N�t�����O�W�٪����ȧe�{������W,�ѿ��-------------- 
          echo "<select name='vendtype'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['vetyno'] . "'>" . $row['vetyname'] . "</option>";
	  }
            echo "</select>";	
	}			
	else 
		echo "�ثe�t�ӵL���O�Ϥ�";
?>
              <input type="hidden" name="venddate" value="<?=date("Y-m-d")?>">
            </td>
          </tr>
          <tr> 
            <td width="103" height="22" align="center">���ʾ��</td>
            <td width="187" height="22"> 
                <input type="text" name="vendsales" size="10">
            </td>
		 </tr>
         <tr>
			<td width="103" height="22" align="center">���q�a�}</td>
            <td width="187" height="22"> 
                <input type="text" name="vendadr" size="40">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">�X�f�a�}</td>
            <td width="187" height="22"> 
                <input type="text" name="vendpradr" size="40">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">�o���a�}</td>
            <td width="187" height="22"> 
                <input type="text" name="vendinadr" size="40">
            </td>           
          </tr>
		  <tr> 
            <td width="103" align="center">�q�l�H�c</td>
            <td width="187"> 
                <input type="text" name="vendemail" size="40">
            </td>
		  </tr>
		  <tr> 
            <td width="96" align="center">���}</td>
            <td width="351"> 
                <input type="text" name="vendhttp" size="40">
            </td>
          </tr>         
        </table>
        <br>        
      </td>
    </tr>
  </table>
</form>
</body>
</html>
