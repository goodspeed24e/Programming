<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
//--------------------�p�ƾ�����----------	
	$cntid="cust";	
	include("counter.php");
	
//------------------ �N�Ȥ����O��ƪ�����ƥ������X---------- 
	$SQLStr = "SELECT * FROM cuty";
	$res = mysql_query($SQLStr);	
?>
<!--------------�������ˬd--------------->
<script>
function validateForm(form1){
	if (!checkCustsname(form1.custsname)){
		alert("�Ȥ�²�� ��Ʀ��~�A���N���e�X�I");
		return(false);	
	}
	alert("��ƥ��T�L�~�A�ߨ�e�X���I");
	form.submit();
	return(true);
}
function checkCustsname(control) {
	ind = control.value.indexOf ('@', 0);
	if (control.value.length==0) {
		alert("�п�J�Ȥ�²�١I");
		return (false);		
	} else
		return (true);
}
</script>
<!------�i�Jcustbasic_act.php �N�Ȥ�򥻸�ƿ�J��Ʈw��---------->
<form name="form1" method="post" action="cust/custbasic_act.php?func=insert">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td   bgcolor="#FFFFFF"> 
        <table width="780" border="1" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">�s�W�Ȥ�򥻸��</font>
            </td> 
            <td align="center"> 
              <input type="submit" name="submit" value="�s�W�Ȥ�">
            </td>
	  </tr>
        </table>
        <table width="780" border="1" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
          <tr> 
            <td width="103" align="center">�Ȥ�Ǹ�</td>
            <td width="187"> 
                <input type="text" name="custno" size="10" value="<?=$custcnt;?>" >
            </td>
            <td width="96" align="center">�Ȥ�²��</td>
            <td width="351"> 
                <input type="text" name="custsname" size="30" onClick="checkCustsname">
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">���q�W��</td>
            <td width="187"> 
                 <input type="text" name="custname" size="40">
            </td>
            <td width="96" align="center">�t�d�H</td>
            <td width="351"> 
                <input type="text" name="custleader" size="10">
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">�Τ@�s��</td>
            <td width="187"> 
                <input type="text" name="custinvoice" size="10">
            </td>
            <td width="96" align="center">�p���H</td>
            <td width="351"> 
                <input type="text" name="custcontact" size="10">
            </td>
          </tr>
		   <tr> 
            <td width="103" align="center">�p���q��</td>
            <td width="187"> 
                <input type="text" name="custtel" size="10">
            </td>
            <td width="96" align="center">�p�����</td>
            <td width="351"> 
                <input type="text" name="custmobil" size="10">
            </td>
          </tr>
          <tr> 
            <td width="103" height="22" align="center">�ǯu��</td>
            <td width="187" height="22"> 
              <input type="text" name="custfax" size="10">
            </td>
            <td width="96" height="22" align="center">�Ȥ����O</td>           
            <td width="187" height="22">
<?php
	if ($res)
	{
	  $num = mysql_num_rows($res);
//--------------- �N�Ȥ����O�W�٪����ȧe�{������W,�ѿ��--------------- 
          echo "<select name='custtype'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['cutyno'] . "'>" . $row['cutyname'] . "</option>";
	  }
            echo "</select>";
	}
//--------------- �Ȥ����O��ƪ��L���O���---------------			
	else 
		echo "�ثe�Ȥ�L���O�Ϥ�";
?>
              <input type="hidden" name="custdate" value="<?=date("Y-m-d")?>">
            </td>
          </tr>
          <tr> 
            <td width="103" height="22" align="center">�~�ȭ�</td>
            <td width="187" height="22"> 
                <input type="text" name="custsales" size="10">
            </td>
		 </tr>
         <tr>
			<td width="103" height="22" align="center">���q�a�}</td>
            <td width="187" height="22"> 
                <input type="text" name="custadr" size="40">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">�e�f�a�}</td>
            <td width="187" height="22"> 
                <input type="text" name="custpradr" size="40">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">�o���a�}</td>
            <td width="187" height="22"> 
                <input type="text" name="custinadr" size="40">
            </td>           
          </tr>
		  <tr> 
            <td width="103" align="center">�q�l�H�c</td>
            <td width="187"> 
                <input type="text" name="custemail" size="40">
            </td>
		  </tr>
		  <tr> 
            <td width="96" align="center">���}</td>
            <td width="351"> 
                <input type="text" name="custhttp" size="40">
            </td>
          </tr>         
        </table>
        <br>        
      </td>
    </tr>
  </table>
</form>
</bady>
</html>