<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
    //-------------- �N�p�ƾ���ƪ��������p�ƭȨ��X--------------	
	$cntid="quot";
	include("counter.php");	

?>
<script language="JavaScript">

//-------------- �ˬd���~�ƶq--------------
function checkprodqty(fld){
   if (fld.value == ""){
      alert("�п�J���~�ƶq!");
      fld.focus();
      fld.select();
   }
}
</script>	

<form name="form1" method="post" action="quotation/quotation_add2.php">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
	 <td   bgcolor="#FFFFFF"> 
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">�s�W��������</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="�s�W��������">
            </td>                 
          </tr>
        </table>	
      <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"  align="center">        
	      <tr> 
            <td width="203" align="center">�����渹</td>
            <td width="187"><input type="text" name="quwkno" size="10" value="<?=$quotcnt;?>">                
            </td>
            <td width="96" align="center">�P�����O</td>
            <td width="251"> 
<?php
    // -------------���X�Ҧ��P�����O�����---------------
    $SQLStr3 = "SELECT * FROM saty";
	$res3 = mysql_query($SQLStr3);
	if ($res3)
	{
	  $num3 = mysql_num_rows($res3);
    //---------- �N�P�����O�s��/�W�٪����ȧe�{������W--------------   
          echo "<select name='quwktype'>";
	  for ($i=0;$i<$num3;$i++)
	  {
	    $row3 = mysql_fetch_array($res3);
	    echo "<option value='" . $row3['satyno'] . "'>" .$row3['satyno'] . $row3['satyname'] . "</option>";
	  }
            echo "</select>";		
	}		
	else 
    //--------------- �P�����O��ƪ��L���O���---------------
		echo "�ثe�P��L���O";
?>         
            </td>
          </tr>
        
          <tr>           
            <td width="196" height="22" align="center">�Ȥ�s��/�W��</td>
           <!-- </td>-->
            <td width="187" height="22">
<?php
    // -------------���X�Ҧ��Ȥ᪺���---------------
    $SQLStr = "SELECT * FROM cust";
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res);
    //---------- �N�Ȥ�s��/�W�٪����ȧe�{������W,�ѿ��--------------   
          echo "<select name='quwkcust'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['custno'] . "'>" .$row['custno'] ." / ". $row['custname'] . "</option>";
	  }
            echo "</select>";		
	}		
	else 
		echo "�ثe�Ȥ�L�Ϥ����O";
?>           
            </td>
			 <td width="96" align="center"></td>
            <td width="251">            
            </td>
          </tr>        
        </table>       
		<table width="780"  border="1"   bgcolor="#99CCFF" cellpadding="0" cellspacing="0" align="center">        
          <tr>
            <td  align="center">���~�s��/���~�W��/���</td>
            <td  align="center">�����ƶq</td>                      
          </tr>
  <?php		  
         //-------------- �N�P�ⲣ�~�s��/�W�٪����ȧe�{������W,�ѿ�ܤο�J�����ƶq--------------
		
		  for ($i=0;$i<8;$i++)
		 { 
              echo "<tr>";
              echo "<td align='center'>";
              //---------- �N���~�s��/�W�٪����ȧe�{������W--------------	
			  $SQLStr = "SELECT * FROM product";
	          $res = mysql_query($SQLStr);
	          if ($res)
	          {
	            $num = mysql_num_rows($res); 
                echo "<select name='quwkprod[]'>";
	            for ($k=0;$k<$num;$k++)
	            {
	              $row = mysql_fetch_array($res);
	              echo "<option value='" . $row['prodno'] . "'>" . $row['prodno'] ."/". $row['prodname'] . "/".$row['prodspric']."</option>";
				  $quwkpric[$k]=$row['prodspric'];
	            }
                  echo "</select>";			
	          }		
	          else 
             //---------- �L���~���--------------------			  
		          echo "�ثe�L���~���";				 
			 echo "</td>";  
             //---------- ��J�����β��~�����ȩ�����W--------------		
             echo "<td align='center'><input name='quwkqty[]' type='text' size='6' maxlength='6' onblur='checkprodqty(this)'></td>";	
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